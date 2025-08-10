## Author

**Mobina Ahmadimasoud, group 24.B83-mm**

## Contacts

st067173@student.spbu.ru

# Skip-List

An STL-style skip list with iterator support.  
Implements a probabilistic ordered data structure supporting fast insertion, deletion, and search with logarithmic average-case complexity.

---

## 📌 Features

- Templated skip list container
- STL-style iterators (`begin()`, `end()`)
- `insert`, `erase`, and `contains` operations
- Efficient memory usage
- Customizable max level and probability
- Full unit test coverage with GoogleTest
- Auto-generated documentation via Doxygen

## Requirements

- **C++17** compatible compiler (GCC, Clang, MSVC)
- **Makefile**
- ** Test** (for unit tests)
- **Doxygen** (for documentation generation)

# build skiplist_demo

make              
./skiplist_demo            

# builds and runs tests
make run_tests    

# removes built binaries
make clean        

# Documentation
doxygen Doxyfile

xdg-open docs/html/index.html
>>>>>>> 675e9d0 (Initial commit on feature/SkipList)
