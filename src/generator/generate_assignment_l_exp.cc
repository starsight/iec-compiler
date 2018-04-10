#include "generate_assignment_l_exp.hh"




/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
void *generate_assign_l_exp_c::visit(                 identifier_c *symbol) { TRACE("identifier_c");  return strdup(symbol->value); }
void *generate_assign_l_exp_c::visit(derived_datatype_identifier_c *symbol) { TRACE("derived_datatype_identifier_c"); return NULL;}
void *generate_assign_l_exp_c::visit(         poutype_identifier_c *symbol) { TRACE("poutype_identifier_c"); return NULL;}




/*********************/
/* B 1.4 - Variables */
/*********************/
void *generate_assign_l_exp_c::visit(symbolic_variable_c *symbol) {
	TRACE("symbolic_variable_c"); 
	int temp_num;
	std::string temp_num_str;
	std::string temp_str;

	temp_str = (char*)symbol->var_name->accept(*this);


  std::cout << "temp_str: " << temp_str << std::endl;

	if((temp_num = pou_info->find_var_return_num(temp_str)) == -1)
	  ERROR_MSG("cannot find the specific variable !");

	temp_num_str = utility_token_get_c::numeric_to_string(temp_num);
	
	return strdup(temp_num_str.c_str());
}


void *generate_assign_l_exp_c::visit(symbolic_constant_c *symbol) {TRACE("symbolic_constant_c"); return symbol->var_name->accept(*this);}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *generate_assign_l_exp_c::visit(direct_variable_c *symbol) {TRACE("direct_variable_c"); return NULL;}


/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
void *generate_assign_l_exp_c::visit(array_variable_c *symbol) {
  TRACE("array_variable_c(generate_assignment_l_exp.cc)");

  std::string subscript = (char *)symbol->subscripted_variable->accept(*this);
  std::cout << "subscripted_variable = " << subscript << std::endl;
  int collector_index = std::stoi(subscript);

  array_type_index = collector_index;

  int * subscript_list = (int *)symbol->subscript_list->accept(*this);//跳转visit(subscript_list_c *symbol)
  //std::cout << "subscript_list = " << subscript_list << std::endl;

  int array_index = *subscript_list;

  if(pou_info->array_var_collector[collector_index].type==TREF){//结构体类型数组 构造成AI_4 数组类型名_struct_var_collector的index
    std::vector<std::string> struct_array_type_var_name = utility_token_get_c::split(pou_info->array_var_collector[collector_index].array_name, " ");
    std::string  struct_array_type_name = struct_array_type_var_name[0];
    int struct_var_collector_index = pou_info->array_var_collector[collector_index].init_value[array_index].v.value_p.value_index;
    std::string IREF_str =struct_array_type_name+"_"+utility_token_get_c::numeric_to_string(struct_var_collector_index);
    std::cout<<IREF_str<<std::endl;
    //直接把信息存到name里，为了程序稳定没有使用这种，但肯定是可以的
    std::cout<<pou_info->array_var_collector[collector_index].init_value[array_index].name<<std::endl;
    int record_num;
	  if((record_num = pou_info->find_var_return_num(IREF_str)) == -1)
	    ERROR_MSG("cannot find the specific variable !");
    //返回这个结构体数组元素在struct_var_collector的位置到void *generate_assign_l_exp_c::visit(structured_variable_c *symbol)中
    return strdup(utility_token_get_c::numeric_to_string(record_num).c_str());
  }
  //pou_info->array_var_collector[collector_index]

  // setfield指令格式：setfield 寄存器A 寄存器B 寄存器C；故需要先加载常量到寄存器中
  std::string temp_code = std::string("kload ");
  std::string temp_reg_numB = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();

  temp_code += temp_reg_numB + std::string(" ");

  IValue iv;
  iv.type = TUINT;
  iv.v.value_u = collector_index;//
  pou_info->constant_value.push_back(iv);

  temp_code += pou_info->get_pou_const_num();
  pou_info->inst_code.push_back(temp_code);
  //********************************************
  temp_code = std::string("kload ");
  std::string temp_reg_numC = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();

  temp_code += temp_reg_numC + std::string(" ");

  iv.type == TUINT;
  iv.v.value_u = array_index;//
  pou_info->constant_value.push_back(iv);

  temp_code += pou_info->get_pou_const_num();
  pou_info->inst_code.push_back(temp_code);
  //********************************************
  std::string retstring = temp_reg_numB + std::string("\\") + temp_reg_numC;
  return strdup(retstring.c_str());

  // return NULL;
}


/* subscript_list ',' subscript */
void *generate_assign_l_exp_c::visit(subscript_list_c *symbol) {
  TRACE("subscript_list_c"); 

  // std::cout<<"n = "<<symbol->n<<std::endl;

  // for(int i = 0; i < symbol->n; i++) {//todo
  //     return utility_token_get_c::return_striped_token((integer_c *)symbol->elements[i]);
  // }
  std::cout<<"n = "<<symbol->n<<std::endl;
	//多维数组每一维长度最好相同　wenjie
	int index=0;
	int row_count=0;

	index =cal_array_offset(pou_info->array_var_collector[array_type_index].each_row_count,symbol);
  	/*for(int i = 0; i < symbol->n; i++) {//todo
    	if(symbol->elements[i]!=NULL){
	  	//std::cout<<"NoT ERROR "<< (char *)(utility_token_get_c::return_striped_token((integer_c *)symbol->elements[i]))<<std::endl;
	  	//row_count = pou_info->array_var_collector[array_index].each_row_count[i];
	  
      	//return utility_token_get_c::return_striped_token((integer_c *)symbol->elements[i]);
    	}
  	}*/
	void *p = &index;
  return p; 
  //return NULL; 
}

int generate_assign_l_exp_c::cal_array_offset_helper(symbol_c *elements){
	return std::stoi((char *)(utility_token_get_c::return_striped_token((integer_c *)elements)));
}
int generate_assign_l_exp_c::cal_array_offset_multi_helper(std::vector<int> each_row_count,int from){
	int multi =1;
	int i=from;
	for(;i<each_row_count.size();i++){
		multi=multi*each_row_count[i];
	}
	std::cout<<"multi = "<<multi<<std::endl;
	return (from==each_row_count.size())?0:multi;
}

int generate_assign_l_exp_c::cal_array_offset(std::vector<int> each_row_count,subscript_list_c *symbol){
	symbol_c **elements = symbol->elements;
	if(each_row_count.size()!=symbol->n)
		return -1;

	int index=0;

	for(int i=0;i<symbol->n;i++){
		int ele_res = cal_array_offset_helper(symbol->elements[i]);//essential error-1.
		if(i==(symbol->n-1)){//最后一个元素
			index += ele_res;//0..ele_res-1 共有ele_res个元素
			break;
		}
		for(int j=0;j<ele_res;j++){
			index +=cal_array_offset_multi_helper(each_row_count,i+1);
		}
	}
	return index;
}


/*  record_variable '.' field_selector */
void *generate_assign_l_exp_c::visit(structured_variable_c *symbol) {
  TRACE("structured_variable_c(generate_assignment_l_exp.cc)");
  std::string field_str = (char*)symbol->field_selector->accept(*this) + innerString;
  innerString = field_str;
  std::string record_str = (char*)symbol->record_variable->accept(*this);
  if(innerflag) return strdup(record_str.c_str());
  innerflag = true;
  int record_num = std::stoi(record_str);
  int field_num = -1;
  std::cout << "record str = " << record_str << std::endl;
  std::cout << "field_str = " << field_str << std::endl;
  // for(int i = 0; i < pou_info->struct_var_collector[record_num].elements.size(); ++i){
  //  std::string temp = pou_info->struct_var_collector[record_num].elements[i].name;
  //  std::cout << temp << std::endl;
  // }
  // /* 获得对应字段在该结构体类型中的索引 */
  for(int i = 0; i < pou_info->struct_var_collector[record_num].elements.size(); i ++){
    std::string temp = pou_info->struct_var_collector[record_num].elements[i].name;
    if(temp == field_str){
      field_num = i;
      break;
    }
  }
  std::cout << "field_num = " << field_num << std::endl;

  // setfield指令格式：setfield 寄存器A 寄存器B 寄存器C；故需要先加载常量到寄存器中
  std::string temp_code = std::string("kload ");
  std::string temp_reg_numB = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();

  temp_code += temp_reg_numB + std::string(" ");

  IValue iv;
  iv.type = TUINT;
  iv.v.value_u = record_num;
  pou_info->constant_value.push_back(iv);

  temp_code += pou_info->get_pou_const_num();
  pou_info->inst_code.push_back(temp_code);
  //********************************************
  temp_code = std::string("kload ");
  std::string temp_reg_numC = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();

  temp_code += temp_reg_numC + std::string(" ");

  iv.type == TUINT;
  iv.v.value_u = field_num;
  pou_info->constant_value.push_back(iv);

  temp_code += pou_info->get_pou_const_num();
  pou_info->inst_code.push_back(temp_code);
  //********************************************
  std::string retstring = temp_reg_numB + std::string("\\") + temp_reg_numC;
  return strdup(retstring.c_str());
  // temp_code = std::string("setfield ");

  // std::string temp_reg_numA = pou_info->get_pou_reg_num();
  // pou_info->inc_pou_reg_num();
  // temp_code += temp_reg_numA;

  // temp_code += std::string(" ") + temp_reg_numB + std::string(" ") + temp_reg_numC;
  // pou_info->inst_code.push_back(temp_code);
  // return strdup(temp_reg_numA.c_str());
  // symbol->record_variable->accept(*this);
  // symbol->field_selector->accept(*this);
  // return NULL;
}



