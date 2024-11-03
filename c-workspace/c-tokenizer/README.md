[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=16031569)
# A0: Word Count

Learning Outcomes
-----------------

1. **Write** a Makefile to compile a simple C program.
2. **Use** raw file I/O functions to open and read files.
3. **Create** a program that will parse file content for display.
4. **Use** memory allocator functions.

Specifications
--------------

For this assignment, you will complete a program that counts the number of words in a file. This is similar to the common Linux tool `wc` (word count). In fact, you can check that your program is functioning correctly by running `wc -w` on the provided input files.

### Buffering Your Own I/O

You must use raw file I/O for this assignment which means you will be filling a buffer of 1024 bytes using the `read()` system call and then parsing text out of that buffer. You should use `strsep()` to parse the text by space or newline character. This will result in a series of non-whitespace tokens that need to be saved in an **array of structs**. When you reach the end of this series of tokens, two things might happen:

1. The filled buffer ends on a word boundary 😀 **OR**
2. The filled buffer ends in the middle of a word 😕

Because this may happen, **you cannot trust the final token in the buffer to be complete**. You must move the (potentially) partial token to the front of the buffer and then fill the buffer starting from where that token ends (so the information is not overwritten). **This is very difficult to get correct**, and if you do not, the resulting word count will not be correct.

Many functions in the C stdlib return values **that are important, do not ignore them**.

### Array of Structs

We need a data structure where each word is associated with its count. This is a good opportunity to use an **array of structs** where the struct is a data structure that consists of the word and the number of times it occurs in the file. This has already been defined for you and given the type name `WORD_T`. An array of these elements is declared as `words` and the size of that array is being tracked with `total_words`. When you encounter a word from the file (complete token), you need to perform a linear search of the array to see if that word has already been enounctered:

1. If it has, you simply increment the `.count` field from the struct.
2. If this is the first time the word has been countered, you must **resize the array** (using `realloc()`) and add the word and the count of 1 to the end of the array.

Since the `word` field in the struct is an array of 42 characters, you can copy the characters from the token to the field using `strcpy()`. Don't forget a _null-terminator_, though.

### Restrictions

* You must compile your program using the flags `std=gnu11`, `-Werror` and `-Wall`.
* You may not write functions or code outside of the locations indicated with `TODO`s (line 29, lines 32-45, line 48).
* You may not use any file stream functions such as `fopen()`, `fread()` or `fclose()`. If you are unsure if a C stdlib function is banned, please just ask.
* You may not `lseek()` or reposition the file pointer (other than by calling `read()`).
* You may not close and reopen the file, you should only need to open it once and read through it a single time.
* You may not use a buffer size other than 1024 bytes.

### Submission

Submit only your completed `wc.c` file and associated `Makefile`. When `make` is executed in the directory, a binary named `wc` should be created. If not, the autograder will fail. You can make a submission as many times as you'd like in order to see the autograder feedback. The maximum points you can receive from the autograder is 8. This is the **Functional** category of the rubric.

### Functions

Here is a list of functions that are used by the solution program. This might help in completing the assignment.

*    `close()`
*    `comparator()`
*    `free()`
*    `lfind()`
*    `memmove()`
*    `open()`
*    `print_and_free()`
*    `printf()`
*    `read()`
*    `realloc()`
*    `strcmp()`
*    `strlen()`
*    `strncpy()`
*    `strsep()`

Example
-------

Here's a sample interaction with a working program. **Your program must not print out anything other than what's shown or the autograder will fail**. The `$` character represents the terminal prompt, you do not type this character when executing commands.

    $ ./wc msno.txt
    MissingNo.: 28
    is: 14
    a: 41
    glitch: 8
    and: 39
    an: 15
    Pokemon: 31
    species: 2
    found: 2
    in: 35
    the: 103
    video: 9
    games: 7
    Red: 5
    Due: 2
    to: 46
    of: 51
    certain: 2
    in-game: 4
    players: 9
    can: 8
    encounter: 7
    via: 2
    glitch.: 3
    It: 2
    one: 3
    most: 3
    famous: 2
    game: 18
    glitches: 5
    all: 2
    graphical: 4
    by: 12
    increasing: 2
    number: 2
    items: 3
    sixth: 2
    player's: 4
    inventory: 2
    glitch's: 2
    guides: 2
    while: 2
    Nintendo: 5
    warned: 3
    that: 25
    encountering: 3
    may: 4
    IGN: 2
    MissingNo.'s: 2
    Blue: 4
    was: 7
    commented: 2
    on: 9
    its: 5
    role: 2
    Fans: 2
    have: 8
    attempted: 2
    incorporate: 2
    as: 30
    part: 3
    games': 3
    actual: 2
    impact: 2
    gaming: 2
    around: 2
    it: 8
    also: 5
    other: 6
    games,: 3
    such: 7
    Vampire: 2
    Survivors: 2
    The: 9
    Binding: 2
    ==: 14
    Game: 3
    published: 2
    series: 2
    with: 12
    for: 5
    In: 9
    these: 2
    player: 12
    goal: 2
    capture: 3
    creatures: 2
    Pokemon.: 2
    abilities: 2
    game's: 8
    travel: 3
    from: 6
    not: 7
    are: 3
    but: 2
    events: 2
    appear: 2
    could: 2
    your: 2
    or: 4
    removed: 2
    so: 2
    games.: 2
    A: 2
    Viridian: 2
    City: 2
    location.: 2
    uses: 2
    move: 2
    Cinnabar: 3
    Island: 2
    up: 2
    generate: 2
    invalid: 2
    area: 2
    within: 2
    data: 4
    be: 6
    encountered: 2
    area.: 2
    this: 4
    used: 2
    tutorial,: 2
    character's: 5
    name: 4
    temporarily: 2
    read: 3
    same: 2
    viewing: 2
    will: 2
    being: 3
    method: 2
    Pokemon,: 2
    MissingNo.,: 2
    item: 2
    which: 3
    another: 2
    appears: 2
    even: 2
    cut: 2
    commonly: 2
    how: 2
    due: 2
    game,: 2
    later: 2
    article,: 3
    helped: 2
    original: 2
    fans: 3
    paper,: 2
    Bainbridge: 2
    his: 4
    Wilma: 2
    2019: 2
    Ars: 2
    at: 5
    belief: 2
    2017: 3
    book: 4
    character: 2
    MissingNo[.]: 2
    forms: 2
    examined: 2
    professor: 2
    added: 3
    world: 2
    Newman: 2
    University: 2
    Lincoln: 2
    fan: 3
    theories: 3
    related: 2
    well: 2
    Miscommunications:: 2
    Errors,: 2
    Mistakes,: 2
    Van: 2
    De: 2
    Nathan: 2
    errors: 2
    glitched: 2
    
    1554 msno.txt

