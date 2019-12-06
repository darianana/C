#pragma once

#include <memory>
#include "Test.hpp"

namespace smart_pointer {

    class exception : std::exception {
        using base_class = std::exception;
        using base_class::base_class;
    };

    template <typename T, typename Allocator>
    class SmartPointer {
        // don't remove this macro
        ENABLE_CLASS_TESTS;

    public:
        using value_type = T;

        explicit SmartPointer(value_type *x = nullptr) {
            if (x != nullptr) {
                core = new Core(x);
            } else {
                core = nullptr;
            }
        }

        SmartPointer(const SmartPointer &src) {
            if (src.core != nullptr) {
                this->core = src.core;
                core->counter++;
            } else {
                core = nullptr;
            }
        }

        SmartPointer(SmartPointer &&src) {
            if (src.core != nullptr) {
                this->core = src.core;
            } else {
                core = nullptr;
            }
            src.core = nullptr;
        }

        SmartPointer &operator=(const SmartPointer &rhs) {
            if (core != NULL){
                core->counter--;
                if(core->counter == 0){
                    delete core;
                }
            }
            if (rhs.core != nullptr) {
                core = rhs.core;
                core->counter++;
            } else {
                core = rhs.core;
            }
            return *this;
        }

        SmartPointer &operator=(SmartPointer &&rhs) {
            if (core != NULL){
                core->counter--;
                if(core->counter == 0){
                    delete core;
                }
            }
            core = rhs.core;
            rhs.core = nullptr;
            return *this;
        }

        SmartPointer &operator=(value_type *x) {
            if (core != NULL){
                core->counter--;
                if(core->counter == 0){
                    delete core;
                }
            }
            if (x != nullptr) {
                core = new Core(x);
            } else {
                core = nullptr;
            }
            return *this;
        }

        ~SmartPointer() {
            if (core != nullptr) {
                core->counter--;
                if (core->counter == 0) {
                    delete core;
                }
            }
        }

        value_type &operator*() {
            if (core != nullptr) {
                return *core->ptr;
            } else {
                throw exception();
            }
        }

        const value_type &operator*() const {
            if (core != nullptr) {
                return *core->ptr;
            } else {
                throw exception();
            }
        }

        value_type *operator->() const {
            if (core != nullptr) {
                return core->ptr;
            } else {
                return nullptr;
            }
        }

        value_type *get() const {
            if (core != nullptr) {
                return core->ptr;
            } else {
                return nullptr;
            }
        }

        operator bool() const { return core != nullptr ? true : false; }

        template <typename U, typename AnotherAllocator>
        bool operator==(const SmartPointer<U, AnotherAllocator> &hh) const {
            return (static_cast<void *>(get()) == static_cast<void *>(hh.get()));
        }

        template <typename U, typename AnotherAllocator>
        bool operator!=(const SmartPointer<U, AnotherAllocator> &hh) const {
            return (static_cast<void *>(get()) != static_cast<void *>(hh.get()));
        }

        std::size_t count_owners() const {
            if (core != nullptr) {
                return core->counter;
            } else {
                return 0;
            }
        }

    private:
        class Core {
        public:
            explicit Core(value_type *x) {
                counter = 1;
                ptr = x;
            }
            ~Core() {
                Allocator allocator;
                allocator.deallocate(ptr, sizeof(value_type));
                ptr = nullptr;
            }
            uint64_t counter;
            value_type *ptr;
        };
        Core *core;
    };
}  // namespace smart_pointer