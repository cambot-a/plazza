
Suggested abstraction:

```cpp
ipc << message;
ipc >> message;
```

---

# Serialization

Pizza data must be serialized before transmission.

Example abstraction:

```cpp
class Packet {
public:
    template<typename T>
    Packet &operator<<(const T &data);

    template<typename T>
    Packet &operator>>(T &data);
};
```

---

# Pizza Enums

```cpp
enum PizzaType
{
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};
```

---

# Main Challenges

- Resource scheduling
- Load balancing
- Serialization
- Deadlock prevention


# EDGE CASES
place an order above the number of cooks