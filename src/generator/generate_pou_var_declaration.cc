#include "generate_pou_var_declaration.hh"





void *generate_pou_var_declaration_c::print_token(token_c *token) {
  // std::cout << "token->value: " <<token->value<<std::endl;
  return NULL;
}



void *generate_pou_var_declaration_c::print_literal(symbol_c *type, symbol_c *value) {

  if (NULL != type) {
    type->accept(*this);
  }
  return value->accept(*this);
  // return NULL;
}

void *generate_pou_var_declaration_c::print_list(list_c *list,
             std::string pre_elem_str ,
             std::string inter_elem_str ,
             std::string post_elem_str ) {

  for(int i = 0; i < list->n; i++) {
    list->elements[i]->accept(*this);
  }

  return NULL;
}


void *generate_pou_var_declaration_c::print_binary_expression(symbol_c *symbol,
            symbol_c *l_exp,
            symbol_c *r_exp,
            const char *operation) {


  l_exp->accept(*this);

  r_exp->accept(*this);

  return NULL;
}

void *generate_pou_var_declaration_c::print_unary_expression(symbol_c *symbol,
           symbol_c *exp,
           const char *operation) {


  exp->accept(*this);
  return NULL;
}



/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
void *generate_pou_var_declaration_c::visit(                 identifier_c *symbol) {
    TRACE("identifier_c"); print_token(symbol);

    std::cout << "symbol->value = " << symbol->value << std::endl;

    return strdup(symbol->value);
}
void *generate_pou_var_declaration_c::visit(derived_datatype_identifier_c *symbol) {
    TRACE("derived_datatype_identifier_c(generate_pou_var_declaration.cc)");
    
    std::cout << "symbol->value = " << symbol->value << std::endl;

    return strdup(symbol->value);
}

void *generate_pou_var_declaration_c::visit(         poutype_identifier_c *symbol) {
    TRACE("poutype_identifier_c(generate_pou_var_declaration.cc)");

    std::cout << "symbol->value = " << symbol->value << std::endl;

    // modified for FB var declaration by wenjie
    //return print_token(symbol); // 原始返回
    return strdup(symbol->value);
}

/*********************/
/* B 1.2 - Constants */
/*********************/
/*********************************/
/* B 1.2.XX - Reference Literals */
/*********************************/
/* defined in IEC 61131-3 v3 - Basically the 'NULL' keyword! */
void *generate_pou_var_declaration_c::visit(ref_value_null_literal_c *symbol)  { TRACE("ref_value_null_literal_c");  return NULL;}

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
void *generate_pou_var_declaration_c::visit(real_c *symbol)               {
  TRACE("real_c"); print_token(symbol);
  return utility_token_get_c::return_striped_token(symbol);
}

void *generate_pou_var_declaration_c::visit(integer_c *symbol)            {
  TRACE("integer_c"); print_token(symbol);
  return utility_token_get_c::return_striped_token(symbol);
}

void *generate_pou_var_declaration_c::visit(binary_integer_c *symbol)     {
  TRACE("binary_integer_c");
  return utility_token_get_c::return_striped_binary_token(symbol, 2);
}

void *generate_pou_var_declaration_c::visit(octal_integer_c *symbol)      { TRACE("octal_integer_c"); return utility_token_get_c::return_striped_octal_token(symbol, 2);}
void *generate_pou_var_declaration_c::visit(hex_integer_c *symbol)        { TRACE("hex_integer_c"); return utility_token_get_c::return_striped_hex_token(symbol, 3);}

void *generate_pou_var_declaration_c::visit(neg_real_c *symbol)           {
  TRACE("neg_real_c");
  std::string temp_str = "-";
  temp_str += (char*)utility_token_get_c::return_striped_token(dynamic_cast<token_c*>(symbol->exp));
  return strdup(temp_str.c_str());
}

void *generate_pou_var_declaration_c::visit(neg_integer_c *symbol)        {
  TRACE("neg_integer_c");
  std::string temp_str = "-";
  temp_str += (char*)utility_token_get_c::return_striped_token(dynamic_cast<token_c*>(symbol->exp));
  return strdup(temp_str.c_str());
}

void *generate_pou_var_declaration_c::visit(integer_literal_c *symbol)    {
  TRACE("integer_literal_c");
  return print_literal(symbol->type, symbol->value);
}
void *generate_pou_var_declaration_c::visit(real_literal_c *symbol)       { TRACE("real_literal_c"); return print_literal(symbol->type, symbol->value);}
void *generate_pou_var_declaration_c::visit(bit_string_literal_c *symbol) { TRACE("bit_string_literal_c"); return print_literal(symbol->type, symbol->value);}
void *generate_pou_var_declaration_c::visit(boolean_literal_c *symbol)    {
  TRACE("boolean_literal_c");
  if (NULL != symbol->type) {
    symbol->type->accept(*this);
  }
  return symbol->value->accept(*this);
}

/* helper class for boolean_literal_c */
void *generate_pou_var_declaration_c::visit(boolean_true_c *symbol)       {
  TRACE("boolean_true_c");
  return strdup("1");
}
void *generate_pou_var_declaration_c::visit(boolean_false_c *symbol)      {
  TRACE("boolean_false_c");
  return strdup("0");
}

/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
void *generate_pou_var_declaration_c::visit(double_byte_character_string_c *symbol) { TRACE("double_byte_character_string_c"); return print_token(symbol);}
void *generate_pou_var_declaration_c::visit(single_byte_character_string_c *symbol) { TRACE("single_byte_character_string_c"); return print_token(symbol);}




/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
void *generate_pou_var_declaration_c::visit(time_type_name_c *symbol)        {TRACE("time_type_name_c");  return strdup("TIME");}
void *generate_pou_var_declaration_c::visit(bool_type_name_c *symbol)        {TRACE("bool_type_name_c");  return strdup("BOOL");}
void *generate_pou_var_declaration_c::visit(sint_type_name_c *symbol)        {TRACE("sint_type_name_c");  return strdup("SINT");}
void *generate_pou_var_declaration_c::visit(int_type_name_c *symbol)         {TRACE("int_type_name_c");  return strdup("INT");}
void *generate_pou_var_declaration_c::visit(dint_type_name_c *symbol)        {TRACE("dint_type_name_c");   return strdup("DINT");}
void *generate_pou_var_declaration_c::visit(lint_type_name_c *symbol)        {TRACE("lint_type_name_c");   return strdup("USINT");}
void *generate_pou_var_declaration_c::visit(usint_type_name_c *symbol)       {TRACE("usint_type_name_c");   return strdup("USINT");}
void *generate_pou_var_declaration_c::visit(uint_type_name_c *symbol)        {TRACE("uint_type_name_c");   return strdup("UINT");}
void *generate_pou_var_declaration_c::visit(udint_type_name_c *symbol)       {TRACE("udint_type_name_c");   return strdup("UDINT");}
void *generate_pou_var_declaration_c::visit(ulint_type_name_c *symbol)       {TRACE("ulint_type_name_c");   return strdup("ULINT");}
void *generate_pou_var_declaration_c::visit(real_type_name_c *symbol)        {TRACE("real_type_name_c");   return strdup("REAL");}
void *generate_pou_var_declaration_c::visit(lreal_type_name_c *symbol)       {TRACE("lreal_type_name_c");   return strdup("LREAL");}
void *generate_pou_var_declaration_c::visit(date_type_name_c *symbol)        {TRACE("date_type_name_c");   return strdup("DATE");}
void *generate_pou_var_declaration_c::visit(tod_type_name_c *symbol)         {TRACE("tod_type_name_c");    return strdup("TOD");}
void *generate_pou_var_declaration_c::visit(dt_type_name_c *symbol)          {TRACE("dt_type_name_c");  return strdup("DT");}
void *generate_pou_var_declaration_c::visit(byte_type_name_c *symbol)        {TRACE("byte_type_name_c");   return strdup("BYTE");}
void *generate_pou_var_declaration_c::visit(word_type_name_c *symbol)        {TRACE("word_type_name_c"); return strdup("WORD");}
void *generate_pou_var_declaration_c::visit(lword_type_name_c *symbol)       {TRACE("lword_type_name_c");  return strdup("LWORD");}
void *generate_pou_var_declaration_c::visit(dword_type_name_c *symbol)       {TRACE("dword_type_name_c");   return strdup("DWORD");}
void *generate_pou_var_declaration_c::visit(string_type_name_c *symbol)      {TRACE("string_type_name_c");  return strdup("STRING");}
void *generate_pou_var_declaration_c::visit(wstring_type_name_c *symbol)     {TRACE("wstring_type_name_c");   return strdup("WSTRING");}

/********************************/
/* B.1.3.2 - Generic data types */
/********************************/
void *generate_pou_var_declaration_c::visit(generic_type_any_c      *symbol) {TRACE("generic_type_any_c");   return NULL;}

/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
/*  TYPE type_declaration_list END_TYPE */
void *generate_pou_var_declaration_c::visit(data_type_declaration_c *symbol) {
  TRACE("data_type_declaration_c");

  symbol->type_declaration_list->accept(*this);

  return NULL;
}


/* helper symbol for data_type_declaration */
/*| type_declaration_list type_declaration ';' */
void *generate_pou_var_declaration_c::visit(type_declaration_list_c *symbol) {
  TRACE("type_declaration_list_c");
  return print_list(symbol,  std::string(""), ";\n" + std::string(""), ";\n");
}


/*  simple_type_name ':' simple_spec_init */
void *generate_pou_var_declaration_c::visit(simple_type_declaration_c *symbol) {
  TRACE("simple_type_declaration_c");
  symbol->simple_type_name->accept(*this);

  symbol->simple_spec_init->accept(*this);
  return NULL;
}


/* simple_specification ASSIGN constant */
void *generate_pou_var_declaration_c::visit(simple_spec_init_c *symbol) {
  TRACE("simple_spec_init_c(generate_pou_var_declaration.cc)");
  var_type = (char*)symbol->simple_specification->accept(*this);

  if (symbol->constant != NULL) {
    std::cout<<"var_value(generate_pou_var_declaration.cc) = "<<var_value<<std::endl;
    var_value = (char*)symbol->constant->accept(*this);
  } else {
    var_value = "0";
  }

  return NULL;
}

/* structure_type_name ASSIGN structure_initialization */
/* structure_initialization may be NULL ! */
void *generate_pou_var_declaration_c::visit(initialized_structure_c *symbol) {
  TRACE("initialized_structure_c(generate_pou_var_declaration.cc)");
  var_type = (char*)symbol->structure_type_name->accept(*this);
  std::cout<<"var_type(initialized_structure_c): "<<var_type<<std::endl;
  if (symbol->structure_initialization != NULL) {
    std::string str = (char *)symbol->structure_initialization->accept(*this);
    std::cout<<"NOT NULL: "<<str<<std::endl;
  }
  return NULL;
}

/* array_specification [ASSIGN array_initialization] */
/* array_initialization may be NULL ! */
void *generate_pou_var_declaration_c::visit(array_spec_init_c *symbol) {// added by wenjie
  TRACE("array_spec_init_c(generate_pou_var_declaration.cc)");
  std::string strTemp = (char*)symbol->array_specification->accept(*this);
  var_type = strTemp;
  std::cout << "strTemp = " << strTemp << std::endl;
  if (symbol->array_initialization != NULL) {
    std::string str = (char *)symbol->array_initialization->accept(*this);
    std::cout<<"NOT NULL: "<<str<<std::endl;
  }
  return NULL;
}


/*********************/
/* B 1.4 - Variables */
/*********************/
void *generate_pou_var_declaration_c::visit(symbolic_variable_c *symbol) {TRACE("symbolic_variable_c"); return symbol->var_name->accept(*this);}
void *generate_pou_var_declaration_c::visit(symbolic_constant_c *symbol) {TRACE("symbolic_constant_c"); return symbol->var_name->accept(*this);}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *generate_pou_var_declaration_c::visit(direct_variable_c *symbol) {TRACE("direct_variable_c"); return print_token(symbol);}


/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
void *generate_pou_var_declaration_c::visit(array_variable_c *symbol) {
  TRACE("array_variable_c");
  symbol->subscripted_variable->accept(*this);

  symbol->subscript_list->accept(*this);

  return NULL;
}


/* subscript_list ',' subscript */
void *generate_pou_var_declaration_c::visit(subscript_list_c *symbol) {TRACE("subscript_list_c"); return print_list(symbol, std::string(""), ", ");}

/*  record_variable '.' field_selector */
void *generate_pou_var_declaration_c::visit(structured_variable_c *symbol) {
  TRACE("structured_variable_c");
  symbol->record_variable->accept(*this);

  symbol->field_selector->accept(*this);
  return NULL;
}


/******************************************/
/* B 1.4.3 - Declaration & Initialisation */
/******************************************/
void *generate_pou_var_declaration_c::visit(constant_option_c *symbol) {TRACE("constant_option_c");  return NULL;}
void *generate_pou_var_declaration_c::visit(retain_option_c *symbol) {TRACE("retain_option_c");  return NULL;}
void *generate_pou_var_declaration_c::visit(non_retain_option_c *symbol) {TRACE("non_retain_option_c");  return NULL;}

/* VAR_INPUT [RETAIN | NON_RETAIN] input_declaration_list END_VAR */
/* option -> the RETAIN/NON_RETAIN/<NULL> directive... */
void *generate_pou_var_declaration_c::visit(input_declarations_c *symbol) {
  TRACE("input_declarations_c");
  pou_info->set_pou_status(POU_STA_VAR_IN_DEC);
  if (typeid(*(symbol->method)) == typeid(explicit_definition_c)) {

    if (symbol->option != NULL)
      symbol->option->accept(*this);

    symbol->input_declaration_list->accept(*this);

  }
  return NULL;
}

/* helper symbol for input_declarations */
/*| input_declaration_list input_declaration ';' */
void *generate_pou_var_declaration_c::visit(input_declaration_list_c *symbol) {
  TRACE("input_declaration_list_c");

  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/* edge -> The F_EDGE or R_EDGE directive */
void *generate_pou_var_declaration_c::visit(edge_declaration_c *symbol) {
  TRACE("edge_declaration_c");
  symbol->var1_list->accept(*this);

  symbol->edge->accept(*this);
  return NULL;
}

/* dummy classes only used as flags! */
void *generate_pou_var_declaration_c::visit(explicit_definition_c *symbol) {TRACE("explicit_definition_c"); return NULL;}
void *generate_pou_var_declaration_c::visit(implicit_definition_c *symbol) {TRACE("implicit_definition_c"); return NULL;}

/* EN : BOOL := 1 */
void *generate_pou_var_declaration_c::visit(en_param_declaration_c *symbol) {
  TRACE("en_param_declaration_c");
  if (typeid(*(symbol->method)) == typeid(explicit_definition_c)) {
    symbol->name->accept(*this);

    symbol->type_decl->accept(*this);
  }
  return NULL;
}

/* ENO : BOOL */
void *generate_pou_var_declaration_c::visit(eno_param_declaration_c *symbol) {
  TRACE("eno_param_declaration_c");
  if (typeid(*(symbol->method)) == typeid(explicit_definition_c)) {
    symbol->name->accept(*this);

    symbol->type->accept(*this);
  }
  return NULL;
}

void *generate_pou_var_declaration_c::visit(raising_edge_option_c *symbol) {
  TRACE("raising_edge_option_c");

  return NULL;
}

void *generate_pou_var_declaration_c::visit(falling_edge_option_c *symbol) {
  TRACE("falling_edge_option_c");

  return NULL;
}


/* var1_list is one of the following...
 *    simple_spec_init_c *
 *    subrange_spec_init_c *
 *    enumerated_spec_init_c *
 */
void *generate_pou_var_declaration_c::visit(var1_init_decl_c *symbol) {
  TRACE("var1_init_decl_c(generate_pou_var_declaration.cc)");
  symbol->var1_list->accept(*this);

  symbol->spec_init->accept(*this);
  if((ivt = pou_info->variable_type_check(var_type)) == TUNDEF){
     ERROR_MSG("variable type check error!");
  }

  for(auto elem : var_name_set) {
    IValue iv;
    iv.type = ivt;
    iv.name = elem;
    if(ivt == TINT) {
      if (!var_value.empty()){
        std::cout << "var_type(TINT) = " << var_type << " name = " << elem << std::endl;
        iv.v.value_i = std::stoi(var_value);
      }
    }
    else if(ivt == TUINT) {
      if (!var_value.empty()){
        std::cout << "var_type(TUINT) = " << var_type << " name = " << elem << std::endl;
        iv.v.value_u = std::stoi(var_value);
      }
    }
    else if(ivt == TDOUBLE) {
      if (!var_value.empty()){
        std::cout << "var_type(DOUBLE) = " << var_type << " name = " << elem << std::endl;
        iv.v.value_d = std::stod(var_value);
      }
    }
    else {
      std::cout << "var_type = " << var_type << " name = " << elem << std::endl;
      iv.v.value_s.str = strdup(var_value.c_str());
      iv.v.value_s.length = strlen(var_value.c_str());
    }
    std::cout<<"get_pou_status= "<<pou_info->get_pou_status()<<std::endl;
    if(POU_STA_VAR_IN_DEC == pou_info->get_pou_status())
      pou_info->input_variable.push_back(iv);
    else if(POU_STA_VAR_OUT_DEC == pou_info->get_pou_status())
      pou_info->output_variable.push_back(iv);
    else if(POU_STA_VAR_INOUT_DEC == pou_info->get_pou_status())
      pou_info->input_output_variable.push_back(iv);
    else if(POU_STA_VAR_LOCAL_DEC == pou_info->get_pou_status())
      pou_info->local_variable.push_back(iv);
    else
      ERROR_MSG("wrong pou status !");

  }
  
  std::cout<<"clear"<<std::endl;
  var_name_set.clear();

  return NULL;
}


void *generate_pou_var_declaration_c::visit(var1_list_c *symbol) {
  TRACE("var1_list_c");

  std::cout << "symbol->n = " << symbol->n << std::endl;
  std::cout << "before, var_name set.size()= " << var_name_set.size() << std::endl;

  for(int i = 0; i < symbol->n; i++) {
    std::string str = (char*)symbol->elements[i]->accept(*this);

    std::cout << "str = " << str << std::endl;

    var_name_set.push_back(str);
  }

  std::cout << "after, var_name set.size()= " << var_name_set.size() << std::endl;
  return NULL;
}

/* fb_name_list ':' function_block_type_name ASSIGN structure_initialization */
/* structure_initialization -> may be NULL ! */
// 函数功能：FB类型的变量的声明（暂时没有做初始化）
// add by wenjie 18-05-16
// 暂时认为FB变量初始化时不会自定义初始化数据信息
void *generate_pou_var_declaration_c::visit(fb_name_decl_c *symbol) {
  TRACE("fb_name_decl_c(generate_pou_var_declaration.cc)");
  /* Please read the comments inside the var1_init_decl_c
   * visitor, as they apply here too.
   */

  /* Start off by setting the current_var_type_symbol and
   * current_var_init_symbol private variables...
   */
  //update_type_init(symbol->fb_spec_init);

  /* now to produce the c equivalent... */
  //symbol->fb_name_list->accept(*this);

  /* Values no longer in scope, and therefore no longer used.
   * Make an effort to keep them set to NULL when not in use
   * in order to catch bugs as soon as possible...
   */
  //void_type_init();

  //return NULL;
  
  // 思路： 先去void *generate_pou_var_declaration_c::visit(fb_name_list_c *symbol)中 
  // 添加到var_name_set，再放入对应变量集合中（如数组就是array_var_collector），最后清空var_name_set
  symbol->fb_name_list->accept(*this);

  // 此行非无用，FB变量的类型名在其中
  symbol->fb_spec_init->accept(*this);

  // 此处参考 void *generate_pou_var_declaration_c::visit(structured_var_init_decl_c *symbol)
  pre_generate_info_c *code_info = pre_generate_info_c::getInstance();
  function_block_type_c temp_fb_var;
  for(auto elem : code_info->fb_type_collector){    // 查找FB变量对应类型
      if(elem.fb_name == var_type){
          temp_fb_var = elem;
          elem.print();
          break;
      }
  }
  // 一般说来 var_name_set 中只有一个元素
  for(auto elem : var_name_set){            // 将FB变量加入FB变量集中
      std::cout << "var_name_set:  "<<elem<< std::endl;
      temp_fb_var.fb_name = var_type + " " + elem; // 将FB变量集中的变量名设为类型名+变量名的形式   如："OR_EDGE CC" "OR_EDGE CE"
      pou_info->fb_var_collector.push_back(temp_fb_var);

      array_struct_fb_info_c temp_info_var;
      temp_info_var.var_name = temp_fb_var.fb_name;
      // 0:struct   1:array   2:fb
      temp_info_var.type = 2;
      temp_info_var.convert_index = pou_info->fb_var_collector.size()-1;
      temp_info_var.origin_index = pou_info->array_struct_fb_info_collector.empty()?0:pou_info->array_struct_fb_info_collector.back().origin_index+1;
      pou_info->array_struct_fb_info_collector.push_back(temp_info_var);
  }

  // for(function_block_type_c elem : pou_info->fb_var_collector){            
  //     std::cout << "elem: "<< elem.fb_name << std::endl;
  // }
  
  std::cout << "END fb_name_decl_c END "<< std::endl;
  var_name_set.clear();

  return NULL;
}

/*  function_block_type_name ASSIGN structure_initialization */
/* structure_initialization -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(fb_spec_init_c *symbol) {
  TRACE("fb_spec_init_c");
  var_type = (char *)symbol->function_block_type_name->accept(*this);
  if (symbol->structure_initialization != NULL) {
    //s4o.print(" := ");
    symbol->structure_initialization->accept(*this);
  }
  return NULL;
}

/* fb_name_list ',' fb_name */
void *generate_pou_var_declaration_c::visit(fb_name_list_c *symbol) {
  TRACE("fb_name_list_c(generate_pou_var_declaration.cc)");
  //declare_variables(symbol, true);
  //return NULL;

  // 此处参考 void *generate_pou_var_declaration_c::visit(var1_list_c *symbol)
  std::cout << "fb_name_list, symbol->n = " << symbol->n << std::endl;
  std::cout << "before, fb_name_list, var_name set.size()= " << var_name_set.size() << std::endl;

  for(int i = 0; i < symbol->n; i++) {
    std::string str = (char*)symbol->elements[i]->accept(*this);

    std::cout << "fb_name_list, str = " << str << std::endl;

    var_name_set.push_back(str);
  }

  std::cout << "after, fb_name_list, var_name set.size()= " << var_name_set.size() << std::endl;

  return NULL;

  //print_list(symbol, "", ", ")
  //return NULL;
}

// 数组变量的（声明）初始化
/* var1_list ':' array_spec_init */ //wenjie
void *generate_pou_var_declaration_c::visit(array_var_init_decl_c *symbol) {
  TRACE("array_var_init_decl_c(generate_pou_var_declaration.cc)");
  symbol->var1_list->accept(*this);
  symbol->array_spec_init->accept(*this);

  pre_generate_info_c *code_info = pre_generate_info_c::getInstance();
  array_type_c temp_array_var;

  std::cout << "array_type_collector-size:  "<<code_info->array_type_collector.size()<< std::endl;

  for(auto elem : code_info->array_type_collector){    // 查找数组对应类型
    std::cout << "elem:  "<<elem.array_name<< std::endl;
    std::cout << "var_type:  "<<var_type<< std::endl;
    // elem 就是声明数组时保存在array_type_collector中的模板
    if(elem.array_name == var_type){
        temp_array_var = elem;

        if(elem.type==TREF){//结构体数组初始化每个IREF  index赋值  wenjie 18-01-15
          struct_type_c temp_struct_var;
          std::string str = temp_array_var.init_value[0].v.value_p.ref_type;
          for(auto s_elem : code_info->struct_type_collector){    // 查找结构变量对应类型
              if(s_elem.struct_name == str ){
                  temp_struct_var = s_elem;
                  //elem.print();
                  break;
              }
          }
          /*for(int i=0;i<temp_array_var.init_value.size();i++){
            int num =pou_info->struct_var_collector.size();
            temp_struct_var.struct_name =  str + " " + elem.array_name+"_"+std::to_string(num); // 将结构体变量集中的变量名设为类型名+数组类型名+index的形式
            pou_info->struct_var_collector.push_back(temp_struct_var);
            temp_array_var.init_value[i].v.value_p.value_index =num;
            
            std::cout<<temp_struct_var.struct_name<<"-"<<num<<std::endl;
          }*/
          for(IValue &ivalue:temp_array_var.init_value){  //&ivalue
            int num =pou_info->struct_var_collector.size();
            temp_struct_var.struct_name =  str + " " + elem.array_name+"_"+std::to_string(num); // 将结构体变量集中的变量名设为类型名+数组类型名+index的形式
            
            pou_info->struct_var_collector.push_back(temp_struct_var);
            ivalue.v.value_p.value_index =num;
            ivalue.name = elem.array_name+"_"+std::to_string(num);//突然发现可以直接把信息存到name里，为了程序稳定没有使用这种，但肯定是可以的
            std::cout<<temp_struct_var.struct_name<<"-"<<num<<std::endl;
            //std::cout<< ivalue.v.value_p.value_index<<std::endl;

            array_struct_fb_info_c temp_info_var;
            temp_info_var.var_name = temp_struct_var.struct_name;
            // 0:struct   1:array   2:fb
            temp_info_var.type = 0;
            temp_info_var.convert_index = pou_info->struct_var_collector.size()-1;
            temp_info_var.origin_index = pou_info->array_struct_fb_info_collector.empty()?0:pou_info->array_struct_fb_info_collector.back().origin_index+1;
            pou_info->array_struct_fb_info_collector.push_back(temp_info_var);
          }
        }

        temp_array_var.print();
        break;
    }
  }
  
  // 不管是不是结构体数组，只要是数组都要添加到array_var_collector中，结构体数组额外再添加到struct_var_collector中（如上）
  for(auto elem : var_name_set){            // 将数组变量加入结构体变量集(应该写错了，是array_var_collector，数组变量集)中
      std::cout << "array_name=  "<<var_type + " elem =" + elem<< std::endl;
      temp_array_var.array_name = var_type + " " + elem; // 将结构体变量集(应该写错了，是array_var_collector，数组变量集)中的变量名设为类型名+变量名的形式
      pou_info->array_var_collector.push_back(temp_array_var);


      array_struct_fb_info_c temp_info_var;
      temp_info_var.var_name = temp_array_var.array_name;
      // 0:struct   1:array   2:fb
      temp_info_var.type = 1;
      temp_info_var.convert_index = pou_info->array_var_collector.size()-1;
      if(temp_array_var.type!=TREF){
        temp_info_var.origin_index = pou_info->array_struct_fb_info_collector.empty()?0:pou_info->array_struct_fb_info_collector.back().origin_index+1;          
      }else{
        temp_info_var.origin_index = pou_info->array_struct_fb_info_collector.empty()?-1:pou_info->array_struct_fb_info_collector.back().origin_index;
      }
      pou_info->array_struct_fb_info_collector.push_back(temp_info_var);
    
  }
  std::cout << "END array_var_init_decl_c END "<< std::endl;
  
  //正确 18-4-9 复核
  var_name_set.clear();//added by wenjie
  return NULL;
}

/*  var1_list ':' initialized_structure */
void *generate_pou_var_declaration_c::visit(structured_var_init_decl_c *symbol) {
  TRACE("structured_var_init_decl_c(generate_pou_var_declaration.cc)");
  symbol->var1_list->accept(*this);

  symbol->initialized_structure->accept(*this);

  pre_generate_info_c *code_info = pre_generate_info_c::getInstance();
  struct_type_c temp_struct_var;
  for(auto elem : code_info->struct_type_collector){    // 查找结构变量对应类型
      if(elem.struct_name == var_type){
          temp_struct_var = elem;
          elem.print();
          break;
      }
  }
  for(auto elem : var_name_set){            // 将结构体变量加入结构体变量集中
      std::cout << "var_name_set:  "<<elem<< std::endl;
      temp_struct_var.struct_name = var_type + " " + elem; // 将结构体变量集中的变量名设为类型名+变量名的形式
      pou_info->struct_var_collector.push_back(temp_struct_var);

      array_struct_fb_info_c temp_info_var;
      temp_info_var.var_name = temp_struct_var.struct_name;
      // 0:struct   1:array   2:fb
      temp_info_var.type = 0;
      temp_info_var.convert_index = pou_info->struct_var_collector.size()-1;
      temp_info_var.origin_index = pou_info->array_struct_fb_info_collector.empty()?0:pou_info->array_struct_fb_info_collector.back().origin_index+1;
      pou_info->array_struct_fb_info_collector.push_back(temp_info_var);
    //   /* 将结构体变量索引信息加入POU变量集中, 暂时放一放 */
    //   IValue iv;
    //   iv.name = elem;
    //   iv.type = TREF;
    //   iv.v.value_p.ref_type = strdup(var_type.c_str());
    //   iv.v.value_p.value_index = pou_info->struct_var_collector.size() - 1;
    //   if(POU_STA_VAR_IN_DEC == pou_info->get_pou_status())
    //     pou_info->input_variable.push_back(iv);
    //   else if(POU_STA_VAR_OUT_DEC == pou_info->get_pou_status())
    //     pou_info->output_variable.push_back(iv);
    //   else if(POU_STA_VAR_INOUT_DEC == pou_info->get_pou_status())
    //     pou_info->input_output_variable.push_back(iv);
    //   else if(POU_STA_VAR_LOCAL_DEC == pou_info->get_pou_status())
    //     pou_info->local_variable.push_back(iv);
    //   else
    //     ERROR_MSG("wrong pou status !");
  }
  std::cout << "END structured_var_init_decl_c END "<< std::endl;
  var_name_set.clear();//added by wenjie
  return NULL;
}

/* VAR_OUTPUT [RETAIN | NON_RETAIN] var_init_decl_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(output_declarations_c *symbol) {
  TRACE("output_declarations_c");
  pou_info->set_pou_status(POU_STA_VAR_OUT_DEC);
  if (typeid(*(symbol->method)) == typeid(explicit_definition_c)) {

    if (symbol->option != NULL)
      symbol->option->accept(*this);

    symbol->var_init_decl_list->accept(*this);

  }
  return NULL;
}

/*  VAR_IN_OUT  END_VAR */
void *generate_pou_var_declaration_c::visit(input_output_declarations_c *symbol) {
  TRACE("input_output_declarations_c");
  pou_info->set_pou_status(POU_STA_VAR_INOUT_DEC);
  symbol->var_declaration_list->accept(*this);
  return NULL;
}

/* helper symbol for input_output_declarations */
/* var_declaration_list var_declaration ';' */
void *generate_pou_var_declaration_c::visit(var_declaration_list_c *symbol) {
  TRACE("var_declaration_list_c");
  return print_list(symbol);
}


/* VAR [CONSTANT] var_init_decl_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(var_declarations_c *symbol) {
  TRACE("var_declarations_c");
  pou_info->set_pou_status(POU_STA_VAR_LOCAL_DEC);
  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->var_init_decl_list->accept(*this);

  return NULL;
}

/*  VAR RETAIN var_init_decl_list END_VAR */
void *generate_pou_var_declaration_c::visit(retentive_var_declarations_c *symbol) {
  TRACE("retentive_var_declarations_c");

  symbol->var_init_decl_list->accept(*this);

  return NULL;
}

/*  VAR [CONSTANT|RETAIN|NON_RETAIN] located_var_decl_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(located_var_declarations_c *symbol) {
  TRACE("located_var_declarations_c");

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->located_var_decl_list->accept(*this);

  return NULL;
}

/* helper symbol for located_var_declarations */
/* located_var_decl_list located_var_decl ';' */
void *generate_pou_var_declaration_c::visit(located_var_decl_list_c *symbol) {
  TRACE("located_var_decl_list_c");
  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/*  [variable_name] location ':' located_var_spec_init */
/* variable_name -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(located_var_decl_c *symbol) {
  TRACE("located_var_decl_c");
  if (symbol->variable_name != NULL) {
    symbol->variable_name->accept(*this);

  }
  symbol->location->accept(*this);

  symbol->located_var_spec_init->accept(*this);
  return NULL;
}


/*| VAR_EXTERNAL [CONSTANT] external_declaration_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(external_var_declarations_c *symbol) {
  TRACE("external_var_declarations_c");

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->external_declaration_list->accept(*this);

  return NULL;
}

/* helper symbol for external_var_declarations */
/*| external_declaration_list external_declaration';' */
void *generate_pou_var_declaration_c::visit(external_declaration_list_c *symbol) {
  TRACE("external_declaration_list_c");
  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/*  global_var_name ':' (simple_specification|subrange_specification|enumerated_specification|array_specification|prev_declared_structure_type_name|function_block_type_name) */
void *generate_pou_var_declaration_c::visit(external_declaration_c *symbol) {
  TRACE("external_declaration_c");
  symbol->global_var_name->accept(*this);

  symbol->specification->accept(*this);
  return NULL;
}

/*| VAR_GLOBAL [CONSTANT|RETAIN] global_var_decl_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(global_var_declarations_c *symbol) {
  TRACE("global_var_declarations_c");

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->global_var_decl_list->accept(*this);

  return NULL;
}

/* helper symbol for global_var_declarations */
/*| global_var_decl_list global_var_decl ';' */
void *generate_pou_var_declaration_c::visit(global_var_decl_list_c *symbol) {
  TRACE("global_var_decl_list_c");
  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
/* type_specification ->may be NULL ! */
void *generate_pou_var_declaration_c::visit(global_var_decl_c *symbol) {
  TRACE("global_var_decl_c");
  symbol->global_var_spec->accept(*this);

  if (symbol->type_specification != NULL)
    symbol->type_specification->accept(*this);
  return NULL;
}

/*| global_var_name location */
void *generate_pou_var_declaration_c::visit(global_var_spec_c *symbol) {
  TRACE("global_var_spec_c");
  symbol->global_var_name->accept(*this);

  symbol->location->accept(*this);
  return NULL;
}

/*  AT direct_variable */
void *generate_pou_var_declaration_c::visit(location_c *symbol) {
  TRACE("location_c");

  symbol->direct_variable->accept(*this);
  return NULL;
}

/*| global_var_list ',' global_var_name */
void *generate_pou_var_declaration_c::visit(global_var_list_c *symbol) {TRACE("global_var_list_c"); return print_list(symbol, std::string(""), ", ");}



/*| VAR [RETAIN|NON_RETAIN] incompl_located_var_decl_list END_VAR */
/* option ->may be NULL ! */
void *generate_pou_var_declaration_c::visit(incompl_located_var_declarations_c *symbol) {
  TRACE("incompl_located_var_declarations_c");

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->incompl_located_var_decl_list->accept(*this);

  return NULL;
}

/* helper symbol for incompl_located_var_declarations */
/*| incompl_located_var_decl_list incompl_located_var_decl ';' */
void *generate_pou_var_declaration_c::visit(incompl_located_var_decl_list_c *symbol) {
  TRACE("incompl_located_var_decl_list_c");
  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/*  variable_name incompl_location ':' var_spec */
void *generate_pou_var_declaration_c::visit(incompl_located_var_decl_c *symbol) {
  TRACE("incompl_located_var_decl_c");
  symbol->variable_name->accept(*this);

  symbol->incompl_location->accept(*this);

  symbol->var_spec->accept(*this);
  return NULL;
}


/*  AT incompl_location_token */
void *generate_pou_var_declaration_c::visit(incompl_location_c *symbol) {
  TRACE("incompl_location_c");

  return print_token(symbol);
}


/* intermediate helper symbol for:
 *  - non_retentive_var_decls
 *  - output_declarations
 */
/* | var_init_decl_list var_init_decl ';' */
void *generate_pou_var_declaration_c::visit(var_init_decl_list_c *symbol) {
  TRACE("var_init_decl_list_c(generate_pou_var_declaration.cc)");
  std::cout<<"var_init_decl_list_c list-length: "<<symbol->n<<std::endl;
  return print_list(symbol,std::string(""), ";\n" + std::string(""), ";\n");
}


/***********************/
/* B 1.5.1 - Functions */
/***********************/

/* intermediate helper symbol for function_declaration */
void *generate_pou_var_declaration_c::visit(var_declarations_list_c *symbol) {
  TRACE("var_declarations_list_c");
  pou_info->set_pou_status(POU_STA_VAR_DEC);
  return print_list(symbol);
}

void *generate_pou_var_declaration_c::visit(function_var_decls_c *symbol) {
  TRACE("function_var_decls_c");
  pou_info->set_pou_status(POU_STA_VAR_LOCAL_DEC);

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->decl_list->accept(*this);

  return NULL;
}

/* intermediate helper symbol for function_var_decls */
void *generate_pou_var_declaration_c::visit(var2_init_decl_list_c *symbol) {
  TRACE("var2_init_decl_list_c");
  print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
  return NULL;
}

/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
/*  VAR_TEMP temp_var_decl_list END_VAR */
void *generate_pou_var_declaration_c::visit(temp_var_decls_c *symbol) {
  TRACE("temp_var_decls_c");

  symbol->var_decl_list->accept(*this);

  return NULL;
}

/* intermediate helper symbol for temp_var_decls */
void *generate_pou_var_declaration_c::visit(temp_var_decls_list_c *symbol) {TRACE("temp_var_decls_list_c"); return print_list(symbol);}

/*  VAR NON_RETAIN var_init_decl_list END_VAR */
void *generate_pou_var_declaration_c::visit(non_retentive_var_decls_c *symbol) {
  TRACE("non_retentive_var_decls_c");

  symbol->var_decl_list->accept(*this);

  return NULL;
}
