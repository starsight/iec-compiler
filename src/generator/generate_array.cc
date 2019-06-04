#include "generate_array.hh"

/*
数组需要以０为起始下标，否则size会出现错误导致一系列问题 多维数组每一维长度最好相同　wenjie 18-01-04
*/



/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
void *generate_array_c::visit(                 identifier_c *symbol) {
    TRACE("identifier_c(generate_array.cc)");
    return strdup(symbol->value);
}

void *generate_array_c::visit(derived_datatype_identifier_c *symbol) {
    TRACE("derived_datatype_identifier_c");
    return strdup(symbol->value);
}

void *generate_array_c::visit(         poutype_identifier_c *symbol) {
    TRACE("poutype_identifier_c");
    return NULL;
}

/*********************/
/* B 1.2 - Constants */
/*********************/
/*********************************/
/* B 1.2.XX - Reference Literals */
/*********************************/
/* defined in IEC 61131-3 v3 - Basically the 'NULL' keyword! */
void *generate_array_c::visit(ref_value_null_literal_c *symbol)  { TRACE("ref_value_null_literal_c");  return NULL;}

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
void *generate_array_c::visit(real_c *symbol)               {
	TRACE("real_c");
#ifdef _CODE_GENERATOR
	return utility_token_get_c::return_striped_token(symbol);
#else
	return NULL;
#endif
}
void *generate_array_c::visit(integer_c *symbol)            {
	TRACE("integer_c");
#ifdef _CODE_GENERATOR
	return utility_token_get_c::return_striped_token(symbol);
#else
	return NULL;
#endif
}
void *generate_array_c::visit(binary_integer_c *symbol)     {
  TRACE("binary_integer_c");
#ifdef _CODE_GENERATOR
  return utility_token_get_c::return_striped_binary_token(symbol, 2);
#else
	return NULL;
#endif
}

void *generate_array_c::visit(octal_integer_c *symbol)      {
	TRACE("octal_integer_c");
#ifdef _CODE_GENERATOR
	return utility_token_get_c::return_striped_octal_token(symbol, 2);
#else
	return NULL;
#endif
}
void *generate_array_c::visit(hex_integer_c *symbol)        {
	TRACE("hex_integer_c");
#ifdef _CODE_GENERATOR
	return utility_token_get_c::return_striped_hex_token(symbol, 3);
#else
	return NULL;
#endif
}

void *generate_array_c::visit(neg_real_c *symbol)           { TRACE("neg_real_c"); return print_unary_expression(symbol, symbol->exp, "-");}
void *generate_array_c::visit(neg_integer_c *symbol)        { TRACE("neg_integer_c"); return print_unary_expression(symbol, symbol->exp, "-");}

void *generate_array_c::visit(integer_literal_c *symbol)    { TRACE("integer_literal_c"); return print_literal(symbol->type, symbol->value);}
void *generate_array_c::visit(real_literal_c *symbol)       { TRACE("real_literal_c"); return print_literal(symbol->type, symbol->value);}
void *generate_array_c::visit(bit_string_literal_c *symbol) { TRACE("bit_string_literal_c"); return print_literal(symbol->type, symbol->value);}
void *generate_array_c::visit(boolean_literal_c *symbol)    { TRACE("boolean_literal_c"); return print_literal(symbol->type, symbol->value);}

/* helper class for boolean_literal_c */
void *generate_array_c::visit(boolean_true_c *symbol)       { TRACE("boolean_true_c");  return NULL;}
void *generate_array_c::visit(boolean_false_c *symbol)      { TRACE("boolean_false_c");  return NULL;}

/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
void *generate_array_c::visit(double_byte_character_string_c *symbol) { TRACE("double_byte_character_string_c"); return print_token(symbol);}
void *generate_array_c::visit(single_byte_character_string_c *symbol) { TRACE("single_byte_character_string_c"); return print_token(symbol);}


/***************************/
/* B 1.2.3 - Time Literals */
/***************************/

/************************/
/* B 1.2.3.1 - Duration */
/************************/
void *generate_array_c::visit(neg_time_c *symbol) { TRACE("neg_time_c"); return NULL;}

void *generate_array_c::visit(duration_c *symbol) {
  TRACE("duration_c");
  if (symbol->neg != NULL)
    symbol->neg->accept(*this);
  symbol->interval->accept(*this);
  return NULL;
}

void *generate_array_c::visit(fixed_point_c *symbol) { TRACE("fixed_point_c"); return print_token(symbol);}

/* SYM_REF5(interval_c, days, hours, minutes, seconds, milliseconds) */
void *generate_array_c::visit(interval_c *symbol) {
    TRACE("interval_c");

  if (NULL != symbol->days) {
    symbol->days->accept(*this);
  }

  if (NULL != symbol->hours) {
    symbol->hours->accept(*this);
  }

  if (NULL != symbol->minutes) {
    symbol->minutes->accept(*this);
  }

  if (NULL != symbol->seconds) {
    symbol->seconds->accept(*this);
  }

  if (NULL != symbol->milliseconds) {
    symbol->milliseconds->accept(*this);
  }

  return NULL;

}



/************************************/
/* B 1.2.3.2 - Time of day and Date */
/************************************/

void *generate_array_c::visit(time_of_day_c *symbol) {
  TRACE("time_of_day_c");
  symbol->daytime->accept(*this);
  return NULL;
}

void *generate_array_c::visit(daytime_c *symbol) {
  TRACE("daytime_c");
  symbol->day_hour->accept(*this);
  symbol->day_minute->accept(*this);
  symbol->day_second->accept(*this);
  return NULL;
}


void *generate_array_c::visit(date_c *symbol) {
  TRACE("date_c");
  symbol->date_literal->accept(*this);
  return NULL;
}

void *generate_array_c::visit(date_literal_c *symbol) {
  TRACE("date_literal_c");
  symbol->year->accept(*this);
  symbol->month->accept(*this);
  symbol->day->accept(*this);
  return NULL;
}

void *generate_array_c::visit(date_and_time_c *symbol) {
  TRACE("date_and_time_c");
  symbol->date_literal->accept(*this);
  symbol->daytime->accept(*this);
  return NULL;
}



/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
void *generate_array_c::visit(time_type_name_c *symbol)        {TRACE("time_type_name_c");  return strdup("TIME");}
void *generate_array_c::visit(bool_type_name_c *symbol)        {TRACE("bool_type_name_c");   return strdup("BOOL");}
void *generate_array_c::visit(sint_type_name_c *symbol)        {TRACE("sint_type_name_c");    return strdup("SINT");}
void *generate_array_c::visit(int_type_name_c *symbol)         {TRACE("int_type_name_c");    return strdup("INT");}
void *generate_array_c::visit(dint_type_name_c *symbol)        {TRACE("dint_type_name_c");    return strdup("DINT");}
void *generate_array_c::visit(lint_type_name_c *symbol)        {TRACE("lint_type_name_c");     return strdup("USINT");}
void *generate_array_c::visit(usint_type_name_c *symbol)       {TRACE("usint_type_name_c");    return strdup("USINT");}
void *generate_array_c::visit(uint_type_name_c *symbol)        {TRACE("uint_type_name_c");      return strdup("UINT");}
void *generate_array_c::visit(udint_type_name_c *symbol)       {TRACE("udint_type_name_c");   return strdup("UDINT");}
void *generate_array_c::visit(ulint_type_name_c *symbol)       {TRACE("ulint_type_name_c");      return strdup("ULINT");}
void *generate_array_c::visit(real_type_name_c *symbol)        {TRACE("real_type_name_c");   return strdup("REAL");}
void *generate_array_c::visit(lreal_type_name_c *symbol)       {TRACE("lreal_type_name_c");  return strdup("LREAL");}
void *generate_array_c::visit(date_type_name_c *symbol)        {TRACE("date_type_name_c");   return strdup("DATE");}
void *generate_array_c::visit(tod_type_name_c *symbol)         {TRACE("tod_type_name_c");   return strdup("TOD");}
void *generate_array_c::visit(dt_type_name_c *symbol)          {TRACE("dt_type_name_c");   return strdup("DT");}
void *generate_array_c::visit(byte_type_name_c *symbol)        {TRACE("byte_type_name_c");   return strdup("BYTE");}
void *generate_array_c::visit(word_type_name_c *symbol)        {TRACE("word_type_name_c");   return strdup("WORD");}
void *generate_array_c::visit(lword_type_name_c *symbol)       {TRACE("lword_type_name_c");   return strdup("LWORD");}
void *generate_array_c::visit(dword_type_name_c *symbol)       {TRACE("dword_type_name_c");   return strdup("DWORD");}
void *generate_array_c::visit(string_type_name_c *symbol)      {TRACE("string_type_name_c");  return strdup("STRING");}
void *generate_array_c::visit(wstring_type_name_c *symbol)     {TRACE("wstring_type_name_c");  return strdup("WSTRING");}

void *generate_array_c::visit(safetime_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safebool_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safesint_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safeint_type_name_c *symbol)     {return NULL;}
void *generate_array_c::visit(safedint_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safelint_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safeusint_type_name_c *symbol)   {return NULL;}
void *generate_array_c::visit(safeuint_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safeudint_type_name_c *symbol)   {return NULL;}
void *generate_array_c::visit(safeulint_type_name_c *symbol)   {return NULL;}
void *generate_array_c::visit(safereal_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safelreal_type_name_c *symbol)   {return NULL;}
void *generate_array_c::visit(safedate_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safetod_type_name_c *symbol)     {return NULL;}
void *generate_array_c::visit(safedt_type_name_c *symbol)      {return NULL;}
void *generate_array_c::visit(safebyte_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safeword_type_name_c *symbol)    {return NULL;}
void *generate_array_c::visit(safelword_type_name_c *symbol)   {return NULL;}
void *generate_array_c::visit(safedword_type_name_c *symbol)   {return NULL;}
void *generate_array_c::visit(safestring_type_name_c *symbol)  {return NULL;}
void *generate_array_c::visit(safewstring_type_name_c *symbol) {return NULL;}

/********************************/
/* B.1.3.2 - Generic data types */
/********************************/
void *generate_array_c::visit(generic_type_any_c      *symbol) {TRACE("generic_type_any_c"); return NULL;}

/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
/*  TYPE type_declaration_list END_TYPE */
void *generate_array_c::visit(data_type_declaration_c *symbol) {
  TRACE("data_type_declaration_c");

  symbol->type_declaration_list->accept(*this);

  return NULL;
}


/* helper symbol for data_type_declaration */
/*| type_declaration_list type_declaration ';' */
void *generate_array_c::visit(type_declaration_list_c *symbol) {
  TRACE("type_declaration_list_c");
  return print_list(symbol, "", "", "");
}


/*  simple_type_name ':' simple_spec_init */
void *generate_array_c::visit(simple_type_declaration_c *symbol) {
  TRACE("simple_type_declaration_c");
  symbol->simple_type_name->accept(*this);

  symbol->simple_spec_init->accept(*this);
  return NULL;
}


/* simple_specification ASSIGN constant */
void *generate_array_c::visit(simple_spec_init_c *symbol) {
  TRACE("simple_spec_init_c(generate_array.cc)");
#ifdef _CODE_GENERATOR
  var_type = (char*)symbol->simple_specification->accept(*this);
  if (symbol->constant != NULL) {
    var_value = (char*)symbol->constant->accept(*this);
    std::cout<<"var_value = "<<var_value<<std::endl;
  } else {
    var_value = "0";
  }
#else
	symbol->simple_specification->accept(*this);
	if (symbol->constant != NULL) {
		symbol->constant->accept(*this);
	}
#endif

  return NULL;
}

/*  subrange_type_name ':' subrange_spec_init */
void *generate_array_c::visit(subrange_type_declaration_c *symbol) {
  TRACE("subrange_type_declaration_c(generate_array.cc)");
  symbol->subrange_type_name->accept(*this);

  symbol->subrange_spec_init->accept(*this);
  return NULL;
}

/* subrange_specification ASSIGN signed_integer */
void *generate_array_c::visit(subrange_spec_init_c *symbol) {
  TRACE("subrange_spec_init_c(generate_array.cc)");
  symbol->subrange_specification->accept(*this);
  if (symbol->signed_integer != NULL) {

    symbol->signed_integer->accept(*this);
  }
  return NULL;
}

/*  integer_type_name '(' subrange')' */
void *generate_array_c::visit(subrange_specification_c *symbol) {
  TRACE("subrange_specification_c(generate_array.cc)");
  symbol->integer_type_name->accept(*this);
  if (symbol->subrange != NULL) {

    symbol->subrange->accept(*this);

  }
  return NULL;
}

/*  signed_integer DOTDOT signed_integer */
void *generate_array_c::visit(subrange_c *symbol) {
  TRACE("subrange_c(generate_array.cc)");
  symbol->lower_limit->accept(*this);

  int upper_limit = std::stoi((char*)symbol->upper_limit->accept(*this)); //得到数组大小
  int lower_limit = std::stoi((char*)symbol->lower_limit->accept(*this)); 

  array_type->each_row_count.push_back(upper_limit-lower_limit+1);
  if(array_type->size==0)
    array_type->size =1;
  array_type->size *= upper_limit-lower_limit+1;//changed by wenjie 不记录每一维度的起始index，所以必须以0作为index起始

  return NULL;
}

/*  enumerated_type_name ':' enumerated_spec_init */
void *generate_array_c::visit(enumerated_type_declaration_c *symbol) {
  TRACE("enumerated_type_declaration_c");
  symbol->enumerated_type_name->accept(*this);

  symbol->enumerated_spec_init->accept(*this);
  return NULL;
}

/* enumerated_specification ASSIGN enumerated_value */
void *generate_array_c::visit(enumerated_spec_init_c *symbol) {
  TRACE("enumerated_spec_init_c");
  symbol->enumerated_specification->accept(*this);
  if (symbol->enumerated_value != NULL) {

    symbol->enumerated_value->accept(*this);
  }
  return NULL;
}

/* helper symbol for enumerated_specification->enumerated_spec_init */
/* enumerated_value_list ',' enumerated_value */
void *generate_array_c::visit(enumerated_value_list_c *symbol) {TRACE("enumerated_value_list_c");  print_list(symbol, "(", ", ", ")"); return NULL;}

/* enumerated_type_name '#' identifier */
void *generate_array_c::visit(enumerated_value_c *symbol) {
  TRACE("enumerated_value_c");
  if (symbol->type != NULL) {
    symbol->type->accept(*this);

  }
  symbol->value->accept(*this);
  return NULL;
}

/*  identifier ':' array_spec_init */
void *generate_array_c::visit(array_type_declaration_c *symbol) {
  TRACE("array_type_declaration_c(generate_array.cc)");
  symbol->identifier->accept(*this);

  symbol->array_spec_init->accept(*this);
  return NULL;
}

/* array_specification [ASSIGN array_initialization} */
/* array_initialization may be NULL ! */
// 入口
// example -> ARRAY[0..9] OF INT := [4(1024), 5(-1024)];
void *generate_array_c::visit(array_spec_init_c *symbol) {
  TRACE("array_spec_init_c(generate_array.cc)");
  // 跳转 void *generate_array_c::visit(array_specification_c *symbol)
  symbol->array_specification->accept(*this);
  if (symbol->array_initialization != NULL) {

    symbol->array_initialization->accept(*this);
  }
  return NULL;
}

// example -> ARRAY[0..9] OF INT
/* ARRAY '[' array_subrange_list ']' OF non_generic_type_name */
void *generate_array_c::visit(array_specification_c *symbol) {
  TRACE("array_specification_c(generate_array.cc)");

  symbol->array_subrange_list->accept(*this);
  std::cout << "########################" << std::endl;
  char *str_type  = (char*)symbol->non_generic_type_name->accept(*this);
  std::cout << "str_type: "<< str_type << std::endl;  
  array_type->type = pre_generate_pou_info_c::variable_type_check(str_type);//声明 type  pre_generate_info.c

  // 因为结构体数组不会有具体的初始化，所以这边全部添加默认的IValue，只是设置了type
  // 当新建一个结构体变量时，直接在下面完成类型声明，加入到array_type_collector，这样就完成了声明部分
  // 对于结构体变量，在generate_pou_var_declaration.cc 
  //                     - void *generate_pou_var_declaration_c::visit(array_var_init_decl_c *symbol)完成变量初始化
  if(array_type->type==TREF){//结构体数组初始化每个IREF
    for(int i=0;i<array_type->size;i++){
      IValue iv;
      iv.v.value_p.ref_type =str_type;
      iv.v.value_p.value_index = 0; //无所谓设不设置，只是为了展示效果改为0值 by wenjie 19-04-09
      /*pre_generate_info_c *code_info = pre_generate_info_c::getInstance();//涉及pou初始化部分，不应写在这里
      for(auto elem : code_info->struct_type_collector){ 
        if(elem.struct_name==str_type){

        }
      }
      iv.value_p.value_index =;*/
      array_type->init_value.push_back(iv);
    }

  }

  std::cout << "########################" << std::endl;
  return NULL;
}

/* helper symbol for array_specification */
/* array_subrange_list ',' subrange */
void *generate_array_c::visit(array_subrange_list_c *symbol) {
    TRACE("array_subrange_list_c(generate_array.cc)");
    // print_list 跳转到 void *generate_array_c::visit(subrange_c *symbol) 获得数组上下限
    print_list(symbol, "", ", ");
    return NULL;
}

// array类型声明 初始化,包括初始化指定的默认值 example -> [4(1024), 5(-1024)]  结构体数组认为不会有默认值
/* helper symbol for array_initialization */
/* array_initial_elements_list ',' array_initial_elements */
void *generate_array_c::visit(array_initial_elements_list_c *symbol) {
    TRACE("array_initial_elements_list_c(generate_array.cc)");
    for(int i = 0; i < symbol->n; i++) {
        // 对于example -> symbol->n =2;
        if(typeid(*(symbol->elements[i])) == typeid(array_initial_elements_c)){
          //跳转至void *generate_array_c::visit(array_initial_elements_c *symbol)
            symbol->elements[i]->accept(*this);
        } else {
            // 不太清楚何时会进入此
            IValue iv;
            if(array_type->type == TINT){
                iv.type = TINT;
                iv.v.value_i = std::stoi((char*)symbol->elements[i]->accept(*this));
            } else if(array_type->type == TUINT){
                iv.type = TUINT;
                iv.v.value_u = std::stoi((char*)symbol->elements[i]->accept(*this));
            } else if(array_type->type == TDOUBLE){
                iv.type = TDOUBLE;
                iv.v.value_d = std::stod((char*)symbol->elements[i]->accept(*this));
            } else if(array_type->type == TSTRING){
                iv.type = TSTRING;
                // 待完成
            } else {
                // 待完成
            }
            array_type->init_value.push_back(iv);
        }
    }
    return NULL;
}

// example ->  5(-1024)
/* integer '(' [array_initial_element] ')' */
/* array_initial_element may be NULL ! */
void *generate_array_c::visit(array_initial_elements_c *symbol) {
  TRACE("array_initial_elements_c(generate_array.cc)");
  int temp_count = 0;
  IValue iv;
  temp_count = std::stoi((char*)symbol->integer->accept(*this));
  //对于example -> temp_count = 5;
  if (symbol->array_initial_element != NULL){   // 取得数组初始值
      if(array_type->type == TINT){
          iv.type = TINT;
          iv.v.value_i = std::stoi((char*)symbol->array_initial_element->accept(*this));
      } else if(array_type->type == TUINT){
          iv.type = TUINT;
          iv.v.value_u = std::stoi((char*)symbol->array_initial_element->accept(*this));
      } else if(array_type->type == TDOUBLE){
          iv.type = TDOUBLE;
          iv.v.value_d = std::stod((char*)symbol->array_initial_element->accept(*this));
      } else if(array_type->type == TSTRING){
          iv.type = TSTRING;
          // 待完成
      } else {
          // 待完成
          // 认为结构体数组不会在声明的时候初始化，所以此部分工作不需要做，
          // 在定义结构体数组变量时转而去使用结构体的初始化，然后存放在结构体变量数组中          
      }
  }
  for(int i = 0; i < temp_count; i ++){
      array_type->init_value.push_back(iv);
  }
  std::cout << "OK" << std::endl;
  return NULL;
}

/*  structure_type_name ':' structure_specification */
void *generate_array_c::visit(structure_type_declaration_c *symbol) {
  TRACE("structure_type_declaration_c");
  symbol->structure_type_name->accept(*this);

  symbol->structure_specification->accept(*this);
  return NULL;
}

/* structure_type_name ASSIGN structure_initialization */
/* structure_initialization may be NULL ! */
void *generate_array_c::visit(initialized_structure_c *symbol) {
  TRACE("initialized_structure_c");
  var_type = (char*)symbol->structure_type_name->accept(*this);
  if (symbol->structure_initialization != NULL) {

    symbol->structure_initialization->accept(*this);
  }
  return NULL;
}

/* helper symbol for structure_declaration */
/* structure_declaration:  STRUCT structure_element_declaration_list END_STRUCT */
/* structure_element_declaration_list structure_element_declaration ';' */
void *generate_array_c::visit(structure_element_declaration_list_c *symbol) {
  TRACE("structure_element_declaration_list_c");

  print_list(symbol, "", "", "");

  return NULL;
}


/*  structure_element_name ':' *_spec_init */
void *generate_array_c::visit(structure_element_declaration_c *symbol) {
  TRACE("structure_element_declaration_c");
  IValue iv; // 临时储存结构体成员
  iv.name = (char*)symbol->structure_element_name->accept(*this);

  symbol->spec_init->accept(*this);

  std::cout << var_type << " " << var_value << std::endl;

  if((iv.type = pre_generate_pou_info_c::variable_type_check(var_type)) == TUNDEF){
     ERROR_MSG("variable type check error!");
  }

  // 数据初始值解析
  if(iv.type == TINT) {
      if (!var_value.empty())
        iv.v.value_i = std::stoi(var_value);
  } else if(iv.type == TUINT) {
      if (!var_value.empty())
        iv.v.value_u = std::stoi(var_value);
  } else if(iv.type == TDOUBLE) {
      if (!var_value.empty())
        iv.v.value_d = std::stod(var_value);
  } else if(iv.type == TSTRING){
      iv.v.value_s.str = strdup(var_value.c_str());
      iv.v.value_s.length = strlen(var_value.c_str());
  } else {
      // 结构体嵌套，待完成
      iv.v.value_p.ref_type = strdup(var_type.c_str());  // 具体的复合数据类型
    //   iv.v.value_p.value_index = var_value; // 具体值
  }
  // struct_type->elements.push_back(iv);
  return NULL;
}

/* helper symbol for structure_initialization */
/* structure_initialization: '(' structure_element_initialization_list ')' */
/* structure_element_initialization_list ',' structure_element_initialization */
void *generate_array_c::visit(structure_element_initialization_list_c *symbol) {TRACE("structure_element_initialization_list_c"); print_list(symbol, "(", ", ", ")"); return NULL;}

/*  structure_element_name ASSIGN value */
void *generate_array_c::visit(structure_element_initialization_c *symbol) {
  TRACE("structure_element_initialization_c");
  symbol->structure_element_name->accept(*this);

  symbol->value->accept(*this);
  return NULL;
}

/*  string_type_name ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init */
void *generate_array_c::visit(string_type_declaration_c *symbol) {
  TRACE("string_type_declaration_c");
  symbol->string_type_name->accept(*this);

  symbol->elementary_string_type_name->accept(*this);
  symbol->string_type_declaration_size->accept(*this);
  if (symbol->string_type_declaration_init != NULL)
    symbol->string_type_declaration_init->accept(*this);
  return NULL;
}

/*  function_block_type_name ASSIGN structure_initialization */
/* structure_initialization -> may be NULL ! */
void *generate_array_c::visit(fb_spec_init_c *symbol) {
  TRACE("fb_spec_init_c");
  symbol->function_block_type_name->accept(*this);
  if (symbol->structure_initialization != NULL) {

    symbol->structure_initialization->accept(*this);
  }
  return NULL;
}



/* ref_spec:  REF_TO (non_generic_type_name | function_block_type_name) */
// SYM_REF1(ref_spec_c, type_name)
void *generate_array_c::visit(ref_spec_c *symbol) {
  TRACE("ref_spec_c");

  symbol->type_name->accept(*this);
  return NULL;
}

/* For the moment, we do not support initialising reference data types */
/* ref_spec_init: ref_spec [ ASSIGN ref_initialization ]; */
/* NOTE: ref_initialization may be NULL!! */
// SYM_REF2(ref_spec_init_c, ref_spec, ref_initialization)
void *generate_array_c::visit(ref_spec_init_c *symbol) {
  TRACE("ref_spec_init_c");
  symbol->ref_spec->accept(*this);
  if (symbol->ref_initialization != NULL) {

    symbol->ref_initialization->accept(*this);
  }
  return NULL;
}

/* ref_type_decl: identifier ':' ref_spec_init */
// SYM_REF2(ref_type_decl_c, ref_type_name, ref_spec_init)
void *generate_array_c::visit(ref_type_decl_c *symbol) {
  TRACE("ref_type_decl_c");
  symbol->ref_type_name->accept(*this);
  symbol->ref_spec_init->accept(*this);
  return NULL;
}



/*********************/
/* B 1.4 - Variables */
/*********************/
void *generate_array_c::visit(symbolic_variable_c *symbol) {
	TRACE("symbolic_variable_c");
	int temp_num;
	std::string temp_num_str;
	std::string temp_str;

	temp_str = (char*)symbol->var_name->accept(*this);

	temp_num_str = utility_token_get_c::numeric_to_string(temp_num);

	return strdup(temp_num_str.c_str());
}


void *generate_array_c::visit(symbolic_constant_c *symbol) {TRACE("symbolic_constant_c"); return symbol->var_name->accept(*this);}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *generate_array_c::visit(direct_variable_c *symbol) {TRACE("direct_variable_c"); return NULL;}


/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
void *generate_array_c::visit(array_variable_c *symbol) {
  TRACE("array_variable_c(generate_array.cc)");
  symbol->subscripted_variable->accept(*this);
  symbol->subscript_list->accept(*this);
  return NULL;
}


/* subscript_list ',' subscript */
void *generate_array_c::visit(subscript_list_c *symbol) {TRACE("subscript_list_c(generate_array.cc)"); return NULL; }

/*  record_variable '.' field_selector */
void *generate_array_c::visit(structured_variable_c *symbol) {
  TRACE("structured_variable_c");
  symbol->record_variable->accept(*this);
  symbol->field_selector->accept(*this);
  return NULL;
}
