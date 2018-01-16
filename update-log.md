### 18-01-16
**修改说明**
- 结构体数组的赋值逻辑添加

**修改文件说明**
- 1. `generate_assignment_l_exp.cc` 对于结构体数组，首先判断为结构体，再拆分成'.'左右进行判断。左边是数组，进入数组的visit函数，先拼接成数组类型名+“_”+index，index来自于`v.value_p.value_index`，然后return在struct_var_collector中的偏移，其实这个过程就是借array的壳，然后最终还是去struct里面查找偏移。
- 2. `generate_assignment_r_exp.cc` 同上。
- 3. `code_linker.cc` 如果是结构体数组，不需要pushback到refval_list。
---
### 18-01-15
**修改说明**
- 结构体数组的变量初始化

**修改文件说明**
- 1.`generate_array.cc` void *generate_array_c::visit(array_specification_c *symbol)初始化结构体数组中的每一个`IValue`的`ref_type`，即ARRAY的类型，这里是结构体名。这边只是添加到`array_var_collector`中，只是类型声明的初始化，之后声明实际变量时，根据这个模板，再修改`index`，放入`struct_var_collector`中，就是真正的变量。
- 2.`generate_pou_var_declaration.cc`void *generate_pou_var_declaration_c::visit(array_var_init_decl_c *symbol) 设置`value_index`，放入`struct_var_collector`（相当于在struct_var_collector中连续存储数组长度个struct类型的变量）。以后根据`ref_type`和`value_index`确定哪个struct位置。每个struct_name为类型+空格+数组类型名+“_”+index（如TUM AI_2）。
