@0xaaaa000000000000;
annotation plugin @0xabcd000000000000(interface) :Text;
# Concrete type of the optional state supplied to activation.
annotation lifecycleState @0xabcde00000000000(interface) :Text;
# Initial allocation hint: list elements, UTF-8 text bytes (excluding NUL), or Data bytes.
# Reserves capacity in generated owning C++ wrappers; does not initialize or limit the field.
annotation hintSize @0xabcdef0000000000(field) :UInt32;
