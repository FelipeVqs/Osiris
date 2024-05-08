#pragma once

// Represents the layout of a virtual method table (vtable) in a Linux system.
struct LinuxVtableLayout {
    // Offset (in bytes) of the offset from the top of the vtable.
    static constexpr std::size_t offset_of_offset_from_top = 0;

    // Offset (in bytes) of the type descriptor pointer in the vtable.
    static constexpr std::size_t offset_of_type_descriptor_pointer = 8;

    // Offset (in bytes) of the first method pointer in the vtable.
    static constexpr std::size_t offset_of_first_method_pointer = 16;
};
