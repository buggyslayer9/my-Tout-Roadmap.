# 25.2 Generics: Write Once, Run Anywhere

In C, if you want a function that finds the largest `int` in an array, and another that finds the largest `float`, you literally have to write two identical functions with different names (`find_largest_int`, `find_largest_float`). 

C macros (`#define`) can fake this, but they are notorious for terrible compiler errors.

Rust uses **Generics** — strongly-typed templates that the compiler writes for you behind the scenes.

## Generic Functions

Let's write a function that takes a slice of *anything* (`&[T]`) and returns a reference to the largest item.

```rust
// `<T>` tells Rust we are using a generic type named T.
// But wait... how does Rust know we can compare `T` using `>`?
// We must restrict T to types that implement the `PartialOrd` trait!
fn find_largest<T: PartialOrd>(list: &[T]) -> &T {
    let mut largest = &list[0];
    
    for item in list {
        if item > largest { // This only compiles because of `T: PartialOrd`
            largest = item;
        }
    }
    
    largest
}

fn main() {
    let number_list = vec![34, 50, 25, 100, 65];
    println!("The largest number is {}", find_largest(&number_list));

    let char_list = vec!['y', 'm', 'a', 'q'];
    println!("The largest char is {}", find_largest(&char_list));
}
```

### What is the Compiler Actually Doing? (Monomorphization)

Rust Generics have **Zero runtime cost**. 
When you compile the code above, the compiler looks at `main()`, sees you used `T` as an `i32` and `T` as a `char`, and silently generates two completely separate, highly-optimized functions in the final machine code. 

## Generic Structs

You can also use generics in your own Data Structures:

```rust
struct Point<T> {
    x: T,
    y: T,
}

// What if x and y need to be different types? Use two generics!
struct MixedPoint<T, U> {
    x: T,
    y: U,
}

fn main() {
    let integer_point = Point { x: 5, y: 10 };       // T is i32
    let float_point = Point { x: 1.0, y: 4.0 };      // T is f64
    
    let mixed = MixedPoint { x: 5, y: 4.0 };         // T is i32, U is f64
}
```

You are already intimately familiar with Generic Enums: `Option<T>` and `Result<T, E>` are just standard library enums utilizing this exact syntax!
