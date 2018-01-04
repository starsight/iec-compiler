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
  
  std::string subscript_list = (char *)symbol->subscript_list->accept(*this);//跳转visit(subscript_list_c *symbol)
  std::cout << "subscript_list = " << subscript_list << std::endl;

  int collector_index = std::stoi(subscript);
  int array_index = std::stoi(subscript_list);

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

  std::cout<<"n = "<<symbol->n<<std::endl;

  for(int i = 0; i < symbol->n; i++) {//todo
      return utility_token_get_c::return_striped_token((integer_c *)symbol->elements[i]);
  }

  return NULL; 
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



