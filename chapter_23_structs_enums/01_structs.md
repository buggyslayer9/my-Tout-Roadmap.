# 23.1 Structs: Beyond C's `struct`

You've written hundreds of `struct`s in C. They group data together. Rust structs do that too, but with one massive upgrade: **Methods**. 

In C, if you wanted to operate on a `Student` struct, you had to pass a pointer to a freestanding function:
```c
// The C Way
typedef struct { ... } Student;
void student_display(const Student *s) { ... }
void student_graduate(Student *s) { ... }
```

In Rust, structs have **Implementations** (`impl` blocks) where you define functions that belong strictly to that struct.

## Defining and Instantiating a Struct

```rust
// 1. Define the data structure
struct Student {
    name: String,
    age: u32,
    gpa: f64,
    active: bool, // Notice there is no trailing semicolon on the struct definition
}

fn main() {
    // 2. Create an instance
    // Note: The ENTIRE struct must be either mutable or immutable.
    // You cannot make just `gpa` mutable.
    let mut ayman = Student {
        name: String::from("Ayman"),
        age: 25,
        gpa: 3.9,
        active: true,
    };
    
    // 3. Access fields with dot notation
    ayman.gpa = 4.0;
}
```

## The `impl` Block and Methods

To make this feel like modern, clean code, we use an `impl` block. Inside, we have two types of functions:
1. **Associated Functions** (like static methods in other languages) - they don't take `self`.
2. **Methods** - they take `&self` (immutable borrow) or `&mut self` (mutable borrow).

```rust
impl Student {
    // 1. Associated Function: A constructor. 
    // Idiomatic Rust calls this `new()`.
    // It returns `Self` (a capitalized alias for `Student`).
    fn new(name: &str, age: u32, gpa: f64) -> Self {
        Student {
            name: String::from(name),
            age, // Shorthand! Because parameter `age` matches field `age`
            gpa,
            active: true,
        }
    }

    // 2. Method (Immutable borrow)
    fn display(&self) {
        println!("{}: age {}, GPA {:.2}", self.name, self.age, self.gpa);
    }

    // 3. Method (Mutable borrow)
    fn graduate(&mut self) {
        self.active = false;
        println!("{} has graduated!", self.name);
    }
}

fn main() {
    // Clean, readable instantiation
    let mut student = Student::new("Ayman", 25, 3.9);
    
    // Clean, readable method calls
    student.display();
    student.graduate();
}
```

Structs in Rust completely replace the need for "Object-Oriented Programming" inheritance hierarchies. You group data, implement methods on it, and combine it with Traits (which we'll see soon).
