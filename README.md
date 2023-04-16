# Smart Ptr Implementation 

Task:
Implement a class for smart pointer (to arbitrary type) with counting references. One object instance can
have several pointers pointing to it. When the object is created or pointer is copied, the counter should
be increased. When the pointer instance is destroyed, the counter should be decreased. When counter
reaches the zero, it means that there is no more using of object and the object instance can be destroyed.
Additional feature: when the pointer is copied (as result of function or getting from field), it should be
checked on null before access to its internal object. The pointer class should implement automatic
verification that it is checked on null before using; if not, the pointer class should print warning (just
printf to stderr)