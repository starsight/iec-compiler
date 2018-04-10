### 18-01-16
**修改说明**
- 结构体数组的赋值逻辑添加

**修改文件说明**
- 1.`generate_assignment_l_exp.cc` 对于结构体数组，首先判断为结构体，再拆分成'.'左右进行判断。左边是数组，进入数组的visit函数，先拼接成数组类型名+“_”+index，index来自于`v.value_p.value_index`，然后return在struct_var_collector中的偏移，其实这个过程就是借array的壳，然后最终还是去struct里面查找偏移。
- 2.`generate_assignment_r_exp.cc` 同上。
- 3.`code_linker.cc` 如果是结构体数组，不需要pushback到refval_list。
- 4.`code_linker.hh` 修改Array时，输出到# OBJ PLC Task Reference Variables Segment下的格式。类型只需要一次性赋值，不需要像结构体，每一个变量都赋予类型。
---
### 18-01-15
**修改说明**
- 结构体数组的变量初始化

**修改文件说明**
- 1.`generate_array.cc` void *generate_array_c::visit(array_specification_c *symbol)初始化结构体数组中的每一个`IValue`的`ref_type`，即ARRAY的类型，这里是结构体名。这边只是添加到`array_var_collector`中（这边应该是笔误，应该是`array_type_collector`），只是类型声明的初始化，之后声明实际变量时，根据这个模板，再修改`index`，放入`struct_var_collector`中，就是真正的变量,同时为了赋值取值时方便，会在`array_var_collector`同时也保留一份变量的信息，但里面不是实际的结构体数组变量（参考`generate_pou_var_declaration.cc`-`void *generate_pou_var_declaration_c::visit(array_var_init_decl_c *symbol)`,`generate_assign_r_exp`-`void *generate_assign_r_exp_c::visit(array_variable_c *symbol)`等）。
- 2.`generate_pou_var_declaration.cc`void *generate_pou_var_declaration_c::visit(array_var_init_decl_c *symbol) 设置`value_index`，放入`struct_var_collector`（相当于在struct_var_collector中连续存储数组长度个struct类型的变量）。以后根据`ref_type`和`value_index`确定哪个struct位置。每个struct_name为类型+空格+数组类型名+“_”+value_index（如TUM AI_2）。
