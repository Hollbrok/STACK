# STACK
## Основная информация об проекте.

![GitHub Release Date](https://img.shields.io/github/release-date/Hollbrok/STACK?style=plastic)

В данном проекте реализована одна из самых основных структур данных __Stack__. Суть этой структуры данных заключается в том, что элементы этой структуры поддерживают принцип __LIFO__ _(“Last in – first out”)_: последним зашёл – первым вышел. Основные функции, с помощью которых мы будем работать со стеком это __push_stack__ и __pop_stack__, примеры их использования будут приведены в самом конце. В реализации так же присутствует многоуровневая защита данных. Защита и грамотная работа __stack__ 'a осуществляется благодаря нескольким простым принципам:
* __Канарейки__ (или же канареечная защита).
* __Hash__ (хэширование данных).
* __Верификатор__ (анализ как достаточно распространенных так и особых случаев, для предотвращения возникновения ошибок или их устранения).

Опять же более подробно об этих принципах будет описано ближе к концу статьи.
Теперь же хочется в кратце показать список (пересказ, если можно так назвать) вещей, которые может наша структура данных.
_______________
- [X] _Полиморфизм_  
    - [X] Тип данных __double__.
    - [X] Тип данных __int__.
    - [X] Тип данных __char__.
    - [X] Тип данных __string__.
    - [X] Тип данных __float__.  
- [X] Структуру _stack_'a.
    - [X] __Канарейки___.
    - [X] Массив типа _type_data_ (в зависимости от типа хранимых данных).
    - [X] Максимальный размер _stack'_ a.
    - [X] Текущий размер _stack'_ a.  
    - [X] __Hash__ _stack'_ a.
- [X] _Конструктор_  _stack'_ a.
    - [X] __Проверки__ на возможные ошибки про вызове конструктора.
        - [X] __Двойной конструктор__.
        - [X] Валидность __максимального размера__  _stack'_ a.
    - [X] Динамическое выделение памяти.
    - [X] Заполнение данныз __POISON'__ ом.
- [X] _Деконструктор_ _stack'_ a.
    - [X] __Проверки__ на возможные ошибки про вызове деконструктора.
        - [X] Полный список находится в описании функции __stack_verify__.
        - [X] __Уровень__ самой проверки варируется в зависимости от требуемого уровня защиты __stack'__ а.  
        - [X] Различные уровни защиты.
            - [X] __LOW__.
            - [X] __MEDIUM__.
            - [X] __HIGH__.
            - [ ] Мега защита, добавляю конструктор копировая.
    - [X] Обеспечение удаления всех данных из стека (_макс._ _размер_, _текущий_ _размер_, _все_ _данные_ _из_ _масива_, _хэша_.)
        - [X] При помощи __POISON__.
    - [X] Освобождение выделенной памяти.
- [X] _push_stack_
    - [X] __Проверки__ на возможные ошибки про вызове функции.
        - [X] Полный список находится в описании функции __stack_verify__.
        - [X] Так же проходит проверка совпадения типов данных и сама проверка __push_number__.
    - [X] Учтено то, что нужно выделять дополнительную память или наоборот освобождать.
        - [X] Написан __реалокатор__.
- [X] _pop_stack_
    - [X] __Проверки__ на возможные ошибки про вызове функции.
        - [X] Полный список находится в описании функции __stack_verify__.
    - [X] Так же учтен тот факт, что нужно увеличивать/уменьшать память, отводимую под хранение данных.
- [X] _stack_dump_
    - [X] Вывод ошибок, если такого существует. И соответственно отсутствие ошибок, если их нет.
    - [X] Вывод всех актуальной информации о стеке.
        - [X] Уровень __защиты данных__.
        - [X] __Имя стека__.
        - [X] __Текущий размер__.
        - [X] __Максимальный размер__.
        - [X] Все __данные__, которые лежат в стеке.
        - [X] Значение __hash__' a _stack'_ a.
        - [X] __Тип данных__, хранимых в _stack'_ e.
    - [X] Учтен тот факт, что данные могут быть разного типа.
- [X] _stack_verify_
    - [X] Проверки
        - [X] __MAX_CAPACITY_ERROR__.
        - [X] __Stack == nullptr__.
        - [X] Проверка на соответствие __hash__ 'a.
        - [X] __stack->data == nullptr__.
        - [X] __Cur_size > max_size__.
        - [X] __Cur_size < 0__.
        - [X] Проверка на валидность значения __max_size__.
        - [X] __Max_size < 0__.
        - [X] Проверка на валидность значения __cur_size__.
        - [X] Проверка на соответствие __канареек__ _stack_ 'a.
        - [X] Проверка на соответствие __канареек__ _stack->data_' ы.
    - [X] В случае ошибки фиксировать ее.
    - [X] Регулировка проверок по уровню защиты
        - [X] __LOW__.
        - [X] __MEDIUM__.
        - [X] __HIGH__.
- [X] _error_print_
    - [X] Возращает __сообщение об ошибки__ в соответсвии с ошибками.
        - [X] Все типы ошибок представлены в _stack_verify_.
- [X] _add_memory_
    - [X] __Проверки__ на возможные ошибки про вызове функции.
        - [X] Полный список находится в описании функции __stack_verify__.
    - [X] Увеличение память на заранее заданную константу __REAL_MULTIPLIER = 2__, если это нужно.
    - [X] Соответственно уменьшение выделенной памяти на заданную константу __REAL_REDUCER = 2 * REAL_MULTIPLIER__ при необходимых условиях.
    - [X] Если начальный размер равен нулю, то размер задается константой __REAL_ADDER__.
    - [X] Все новые данных (или все удаленне) заполняются ___POISON'_ ом.
- [X] _hash_stack_
    - [X] __Проверки__ на возможные ошибки про вызове функции.
        - [X] Полный список находится в описании функции __stack_verify__.
    - [X] Хэширование данных в стеке.
        - [X] Все хранящиеся __данные__.
        - [X] __имя стека__.
        - [X] __Указателей__.
- [X] _define_lvl_
    - [X] Определяет __уровень защиты__ в требованию пользователя.
______________
### ~~Ded's weakness~~ cats 😻
______________    
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄.  
⠄⠄⠄⠄⠄⠄⢰⣷⡄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄  
⠄⠄⠄⠄⣠⣾⣿⣿⣷⣦⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄  
⠄⠄⠄⣠⣿⣿⣿⣿⣿⣿⣇⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄  
⠄⠄⠄⠄⠛⠿⣿⣿⣿⣿⣿⣆⠄⠄⠄⠄⠄⣴⣿⣿⣆⠄⠄⠄  
⠄⠄⠄⠄⠄⣰⣿⣿⣿⣿⣿⣿⣷⣄⠄⠄⠄⣿⣿⠛⠉⠄⠄⠄   
⠄⠄⠄⠄⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠄⠘⣿⡆⠄⠄⠄⠄   
⠄⠄⠄⠄⠄⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠸⣿⡀⠄⠄⠄  
⠄⠄⠄⠄⠄⠄⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⣿⡇⠄⠄⠄  
⠄⠄⠄⠄⠄⠄⢸⣿⡟⣿⣿⣿⣿⣿⣿⣿⣿⡇⢀⣿⠇⠄⠄⠄  
⠄⠄⠄⠄⠄⢀⣸⡿⢁⣘⣿⣿⣿⣿⣿⣿⣿⣇⣼⠋⠄⠄⠄⠄  
⠄⠄⠄⠄⠄⠻⠿⠓⠿⠿⠿⠿⠿⠿⠿⠿⠿⠛⠁⠄⠄⠄⠄⠄  
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄  
______________________  
.......................／＞　 フ.....................  
　　　　　| 　_　 _ |  
　 　　　／`ミ _x 彡  
　　 　 /　　　 　 |  
　　　 /　 ヽ　　 ﾉ  
　／￣|　　 |　|　|  
　| (￣ヽ____ヽ___)___)  
　＼二つ  
 _____________________