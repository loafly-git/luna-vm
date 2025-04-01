These rules mostly apply to C++.

##### Table of Contents
- Styling
  - [Indentation](#indentation)<br>
  - [Naming](#naming)<br>
  - [General](#general)<br>
  - [Include](#include)<br>
  - [Headers](#headers)<br>
- Design
  - [STL](#stl)<br>

<a name="indentation"/>

## Indentation
Use 4 spaces, do **not** use tabs.

When writing multiline function arguments, try to keep them in the same column as much as possible:
```cpp
// Bad
void SomeFunction(FooInfo Info,
    Bar& Bar,
    ThingType Thing);

// Bad
void SomeFunction(
    FooInfo Info,
    Bar& Bar,
    ThingType Thing
);

// Good
void SomeFunc(FooInfo Info,
              Bar& Bar
              ThingType Thing);
```

This also applies when passing arguments.

<a name="naming"/>

## Naming
All code, files, directories and comments should be written in English.

Everything is generally in **PascalCase** (every first letter of a word capitalized). With the exception of macros and certain type aliases.

- Use verbs for functions, nouns for variables, filenames, and types.
- When writing functions and variable names, try to keep it **concise and descriptive**. And with the _reader_ in mind.
  - Don't use ambiguous names, such as `I`, `J`, or `K`.<br>
    Instead use verbose names such as `Begin`, `End` or `Index`.

<a name="general"/>

## General
- Try your best to keep a line under 80 columns
  - If it makes readibility worse, you're allowed to ignore this.
- Encapsulate everything within the `Luna` namespace.
- Put brackets on a newline:
  - ```cpp
    // Bad
    void SomeFunction() {

    }

    // Good
    void SomeFunction()
    {

    }
    ```
  - Do this even for statements that can be in a single line (such as returning from `if`).
- Break code into smaller functions. Functions should do one thing and one thing only.
  Consider `inline` whenever appropriate, but use them with caution (TODO: why?)
  

<a name="stl"/>

## STL
The usage of STL is allowed *but limited*.

Luna aims to be **exception-free** as a library, and not all STL libraries are safe from exceptions.<br>
As of right now I haven't fully decided due to how early the codebase is.

But here is the general outline:
- Use containers from STL
  - For the commonly used `std::vector` try to properly check bounds, or
  - preallocate using `reserve()` to avoid allocation exceptions.
- `std::string` may be safe to use, but be aware of user inputs (arguments, configurations).
- If a library relies heavily on exceptions, either avoid them or find a workaround.

<a name="include"/>

## Include
You should always **include what you need**.<br>
Do NOT rely on other headers that is including what you need, be clear of what you are using.

Use forward declaration when you need something from another class inside a header file.

Always use full paths, even if the files are under the same directory.
> Except when including the header you are implementing.

Includes should be grouped in this order
- Interface to implement _(if any)_
- Standard library files
- C includes (standard C, POSIX, etc. _if any_)
- Third party files
- Project files

Sort your includes in lexicographical order and separate each group with an empty newline.

Example:
```cpp
#include "Interface.h"

#include <algorithm>
#include <bitset>
#include <ctime>
#include <deque>

#include <fcntl.h>
#include <signal.h>

#include <ThirdParty.h>

#include "Bar/AFoo.h"
#include "Bar/Boo.h"
#include "Foo/CBar.h"
```

<a name="headers"/>

## Headers
Write `#pragma once` at the beginning of header files.

Keep implementation details **out** from headers. Headers are public facing and should not expose internal behavior.

However, an exception can be made for template functions. If explicit instatiation or wrapping function sacrifices readability, then it is **acceptable** to provide the definition inside the header.

Always encapsulate within the namespace `Luna`:
```cpp
#pragma once

namespace Luna
{

<...>

} // namespace Luna
```
