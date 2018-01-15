
---
### 18-01-15
- 结构体数组的变量初始化
修改文件说明：
`generate_array.cc` void *generate_array_c::visit(array_specification_c *symbol)初始化结构体数组中的每一个`IValue`的`ref_type`，即ARRAY的类型，这里是结构体名。这边只是添加到`array_var_collector`中，只是类型声明的初始化，之后声明实际变量时，根据这个模板，再修改`index`，放入`struct_var_collector`中，就是真正的变量。
`generate_pou_var_declaration.cc`void *generate_pou_var_declaration_c::visit(array_var_init_decl_c *symbol) 设置`value_index`，放入`struct_var_collector`（相当于在`struct_var_collector`中连续存储数组长度个struct类型的变量）。以后根据`ref_type`和`value_index`确定哪个struct位置。每个`struct_name`为类型+空格+数组名+“_”+index（如TUM AI_2）
