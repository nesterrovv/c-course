// используйте typedef чтобы определить ftype

// function, struct array & int64_t are patemetres and  size_t type for return (necessary as 2nd param for ftype function from task)
typedef size_t help_function(struct array, int64_t);

// the ftype function itself
typedef char ftype(const float*, help_function);
