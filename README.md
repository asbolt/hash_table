# Хэш-таблица

Данный проект демонстрирует несколько видов оптимизаций на примере хэш-таблицы

Саша хэш-таблица реализована методом ззакрытой адресации (метод цепочек), т.е. использует списки для хранения элементов с одинаковым хэш-значением. Этот метод был выбран, т.к. метод цепочек прост в реализации и легко справляется с высокой загрузкой таблицы.

Выглядит это примерно так:  

![Хэш-таблица методом цепочек](https://github.com/asbolt/hash_table/raw/main/images/hash_table.png)
  
Конкретно данная программа будет создавать хэш-таблицу из текстового файла, а потом много раз искать слова в ней.

## Оптимизация с помощью интринсиков

Для поиска узких мест в программе будем использовать профилировщик gprof (перед запуском были созданы обертки для библиотечных функций).

Итак, в первом отчете мы видим таких лидеров по затраченному времени:

![Первый отчет](https://github.com/asbolt/hash_table/raw/main/images/profile1.png)

фуункция hash_table_find_element по сути является dump'ом в программе и состоит в основном из принтфов. Это не часть реализуемого алгоритма, поэтому для оптимизаций эта функция не подходит. Поэтому попробуем переписать strcmp:

```
int mystrcmp(const char *str1, const char *str2)
{
    __m256i st2 = _mm256_set_epi8 ( str2[31], str2[30], str2[29], str2[28], str2[27], str2[26], str2[25],
                                    str2[24], str2[23], str2[22], str2[21], str2[20], str2[19], str2[18], 
                                    str2[17], str2[16], str2[15], str2[14], str2[13], str2[12], str2[11], 
                                    str2[10], str2[9], str2[8], str2[7], str2[6], str2[5], str2[4], str2[3], 
                                    str2[2], str2[1], str2[0]);
    __m256i st1 = _mm256_set_epi8 ( str1[31], str1[30], str1[29], str1[28], str1[27], str1[26], str1[25],
                                    str1[24], str1[23], str1[22], str1[21], str1[20], str1[19], str1[18], 
                                    str1[17], str1[16], str1[15], str1[14], str1[13], str1[12], str1[11], 
                                    str1[10], str1[9], str1[8], str1[7], str1[6], str1[5], str1[4], str1[3], 
                                    str1[2], str1[1], str1[0]);

    __m256i sub = _mm256_sub_epi8(st1, st2);
    int cmp = _mm256_movemask_epi8(sub);

    return cmp;
}
```

Снова запускаем профиллировщик и... Ого, теперь программа работает в 1.88 раз быстрее!

![Второй отчет](https://github.com/asbolt/hash_table/raw/main/images/profile2.png)

## Отимизация с помощью встроенного ассемблера

Рассмотрим обновленный список "лидеров". На втором месте теперь функция hash_table_find_element. Однако, много времени она занимает за счет разыменовывания указателей. Что ж, в этом мы ей помочь не можем, такой уж алгоритм. Но мы можем попытаться ускорить функцию strlen (следующую в списке и, к слову, часть hash_table_find_element)

Вот так выгядела обертка strlen до:

```
int mystrlen(const char *str)
{
    int size = strlen (str);
    printf("size: %d\n", size);
    return size;
}
```

И вот как мы над ней поиздевались:

```
int mystrlen(const char *str)
{
    int size = 0;

    asm(".intel_syntax noprefix\n\t"
        "xor ebx, ebx\n\t"
        "mov rax, %1\n\t"    
        "inc ebx\n\t"
        "next:\n\t"  
        "cmp byte [rax], bh\n\t" 
        "je ending\n\t"
        "inc ebx\n\t"
        "inc rax\n\t"
        "jmp next\n\t"
        "ending:\n\t"
        "inc ebx\n\t"
        "inc rax\n\t"
        "mov %0, ebx\n\t"
        ".ATT_syntax prefix\n\t"
        :"=r"(size) 
        :"r"(str)
        : "rax", "ebx"
    );

    return size;
}
```

Проверим результат:

![Третий отчет](https://github.com/asbolt/hash_table/raw/main/images/profile3.png)

Снова значительное ускорение: в 1.12 раз! Тут даже пришлось увеличить количество поисков для одного элемента в 5 раз, чтобы профилировщик справился что-нибудь посчитать.


## Оптимизация с помощью своей ассемблерной функции

В последнем отчете на втором месте неожиданно выбраалсь функция хэширования. Для полноты картины попробуем написать точно такой же алгоритм на ассемблере.

Вариант на си:

```
int hash_word (const char *word)
{
    assert (word);

    size_t word_size = strlen (word);
    int hash = 0;

    for (size_t symbol = 0; symbol < word_size; symbol++)
    {
        hash += (int)word[symbol];
    }

    return (hash % HASH_TABLE_SIZE);
}
```

Вариант на ассемблере:

```
section .text
    global hash_word

hash_word:
    push rbp
    mov rbp, rsp
    push rbx

    xor rbx, rbx
    xor rax, rax
.next:
    mov bl, byte [rdi]
    add rax, rbx
    cmp bl, 0
    je .ending
    inc rdi
    jmp .next

.ending:
    shr rax, 7
    pop rbx
    leave
    ret

```

Получаем:

![Четвертый отчет](https://github.com/asbolt/hash_table/raw/main/images/profile4.png)

Невероятно, ускорение в 1,16 раз!

## Заключение

Коэффициент ускорения после последней оптимизации все еще высок и очевидно, что есть смысл продолжать оптимизации. Однако, так как это учебный проект, мы ограничимся только тремя итерациями.