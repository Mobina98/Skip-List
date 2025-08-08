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

# Run the executable

make              # builds skiplist_demo

./skiplist_demo

# Build and run tests

make              # builds skiplist_demo
make run_tests    # builds and runs tests
make clean        # removes built binaries

# Documentation

doxygen Doxyfile
>>>>>>> 675e9d0 (Initial commit on feature/SkipList)
