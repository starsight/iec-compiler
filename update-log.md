
### 18-05-16
**修改说明**
- 1.一个预处理，四大步骤。
- 2.预处理：为了形成连续的寄存器组，先选择构建`inout,out,local`变量的传入；再像函数一样添加input形参，最后把之前构建好的放在后面。因为构建过程会破坏寄存器连续，但又要保证先添加input，所以用vector保存对应的寄存器号。
- 3.步骤一：遍历输入参数（两种形式），将对应值mov到寄存器中。
- 4.步骤二：根据预处理，添加`inout,out,local`变量到寄存器组，放在步骤一的后面。
- 5.步骤三：ucall指令跳转到相应代码段。
- 6.保存`inout,output,local`到对应寄存器,成功运行的前提是运行平台把数据拷贝回了原来的寄存器， 即 "ret (extra_save_base_num)" 语句被执行（实际代码为ret 0 0，这样看运行平台的处理），参见谭伯龙论文对`ucall/ret`语句的解释。

**修改文件说明**
- 1.`generate_iec.cc`中`void *visit(fb_invocation_c *symbol)`完成所有步骤；`void *load_fb_args_helper`和`void *save_fb_args_helper`辅助完成读和写。
---
### 18-05-16
**修改说明**
- 1.把FB的使用流程按照**类型声明，变量定义初始化，语句调用，code_link&translator**，添加相关函数。
- 2.目前FB的处理思路为：先按照POU的处理模式把数据信息和代码信息记录下来，再把数据信息另外存储到功能块的描述类（`fb_type_collector`和`fb_var_collector`）中，这个存储过程和数组、结构体复杂数据结构是一致的（两个collector形式类似）。
- 3.初步完成FB类型声明和变量声明的存储操作。定位下一步的问题在`struct`和`function_block`的区分上，同时FB变量调用FB代码的语句与平常赋值语句不在一个流程线上，在`visit(fb_invocation_c *symbol)`中处理其，有待完成。
- 4.`fb_type_collector`赋值在`generate_iec.cc`的`void *visit(function_block_declaration_c *symbol)`中；`fb_var_collector`赋值在`generate_pou_var_declaration`的`void *generate_pou_var_declaration_c::visit(fb_name_decl_c *symbol) `中。
- 5.其他待完成可通过搜索"TODO"定位（目前一处）。

**修改文件说明**

- 1.使用流程的前半部分主要函数梳理，值得注意的是`visit(fb_invocation_c *symbol)`是FB的程序语句代码的执行入口，作为对比，一般赋值语句在`generate_iec.cc`中的`void *visit( assignment_statement_c *symbol)`作为语句代码的入口（师兄对**寄存器的操作**及**指令码生成**全在此函数内部进行）。

| 文件                            |                                        函数 |    功能    |
| ------------------------------- | ------------------------------------------- | --------- |
| generate_iec.cc                 | visit(function_block_declaration_c *symbol) | FB类型声明 |
| generate_pou_var_declaration.cc |               visit(fb_name_decl_c *symbol) | FB变量声明 |
| generate_iec.cc                 |              visit(fb_invocation_c *symbol) | 调用FB中的语句 |

- 2.增加**功能块描述类**`function_block_type_c`，位置在`pre_generate_info.hh`中，与结构体(`struct_type_c`)，数组(`array_type_c`)描述类对应。
- 3.增加**FB类型**存储集合`fb_type_collector`，**FB类型变量**存储集合`fb_var_collector`。位置在`pre_generate_info.hh`中，与结构体，数组类型（和变量）存储集合对应。
- 4.增加`pre_generate_info.cc`中函数`find_var_return_num`对`fb_var_collector`中变量的查找。
---
### 18-05-15
**修改说明**
- 1.`code link`过程的修改

**修改文件说明**
- 1.根据`translator.cc`发现`code_linker.cc`中对引用类型变量的编译生成描述形式的错误。原来为`S TUM TINT 1 TINT 2`形式，改为`S 2 TINT 1 TINT 2`，即第二个参数为这个复杂数据结构中的元素个数，而不是类型名。
---
### 18-05-14
**修改说明**
- 1.增加生成translator.exe的Makefile的gdb调试参数

**修改文件说明**
- 1.`../src/objgen/Makefile`增加`-g`参数
---
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
