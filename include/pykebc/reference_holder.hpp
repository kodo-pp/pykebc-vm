#pragma once

#include <memory>


template <typename T>
class ReferenceHolder final
{
public:
    ReferenceHolder(T* object) noexcept:
        object(object)
    { }

    ~ReferenceHolder() noexcept
    {
        if (object != nullptr) {
            --object->ref_count;
            if (object->ref_count == 0) {
                delete object;
            }
        }
    }

    void invalidate() noexcept
    {
        object = nullptr;
    }

private:
    T* const object = nullptr;
};
