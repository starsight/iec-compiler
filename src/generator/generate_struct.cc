#include "generate_struct.hh"




/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
void *generate_struct_c::visit(                 identifier_c *symbol) {
    TRACE("identifier_c(generate_struct_c.cc)");
    return strdup(symbol->value);
}

void *generate_struct_c::visit(derived_datatype_identifier_c *symbol) {
    TRACE("derived_datatype_identifier_c(generate_struct_c.cc)");
    return strdup(symbol->value);
}

void *generate_struct_c::visit(         poutype_identifier_c *symbol) {
    TRACE("poutype_identifier_c(generate_struct_c.cc)");
    return NULL;
}

/*********************/
/* B 1.2 - Constants */
/*********************/
/*********************************/
/* B 1.2.XX - Reference Literals */
/*********************************/
/* defined in IEC 61131-3 v3 - Basically the 'NULL' keyword! */
void *generate_struct_c::visit(ref_value_null_literal_c *symbol)  { TRACE("ref_value_null_literal_c(generate_struct_c.cc)");  return NULL;}

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
void *generate_struct_c::visit(real_c *symbol)               {
	TRACE("real_c(generate_struct_c.cc)");
#ifdef _CODE_GENERATOR
	return utility_token_get_c::return_striped_token(symbol);
#else
	return NULL;
#endif
}
void *generate_struct_c::visit(integer_c *symbol)            {
	TRACE("integer_c(generate_struct_c.cc)");
#ifdef _CODE_GENERATOR
	return utility_token_get_c::return_striped_token(symbol);
#else
	return NULL;
#endif
}
void *generate_struct_c::visit(binary_integer_c *symbol)     {
  TRACE("binary_integer_c(generate_struct_c.cc)");
#ifdef _CODE_GENERATOR
  return utility_token_get_c::return_striped_binary_token(symbol, 2);
#else
	return NULL;
#endif
}

void *generate_struct_c::visit(octal_integer_c *symbol)      {
	TRACE("octal_integer_c(generate_struct_c.cc)");
#ifdef _CODE_GENERATOR
	return utility_token_get_c::return_striped_octal_token(symbol, 2);
#else
	return NULL;
#endif
}
void *generate_struct_c::visit(hex_integer_c *symbol)        {
	TRACE("hex_integer_c(generate_struct_c.cc)");
#ifdef _CODE_GENERATOR
	return utility_token_get_c::return_striped_hex_token(symbol, 3);
#else
	return NULL;
#endif
}

void *generate_struct_c::visit(neg_real_c *symbol)           { TRACE("neg_real_c(generate_struct_c.cc)"); return print_unary_expression(symbol, symbol->exp, "-");}
void *generate_struct_c::visit(neg_integer_c *symbol)        { TRACE("neg_integer_c(generate_struct_c.cc)"); return print_unary_expression(symbol, symbol->exp, "-");}

void *generate_struct_c::visit(integer_literal_c *symbol)    { TRACE("integer_literal_c(generate_struct_c.cc)"); return print_literal(symbol->type, symbol->value);}
void *generate_struct_c::visit(real_literal_c *symbol)       { TRACE("real_literal_c(generate_struct_c.cc)"); return print_literal(symbol->type, symbol->value);}
void *generate_struct_c::visit(bit_string_literal_c *symbol) { TRACE("bit_string_literal_c(generate_struct_c.cc)"); return print_literal(symbol->type, symbol->value);}
void *generate_struct_c::visit(boolean_literal_c *symbol)    { TRACE("boolean_literal_c(generate_struct_c.cc)"); return print_literal(symbol->type, symbol->value);}

/* helper class for boolean_literal_c */
void *generate_struct_c::visit(boolean_true_c *symbol)       { TRACE("boolean_true_c(generate_struct_c.cc)");  return NULL;}
void *generate_struct_c::visit(boolean_false_c *symbol)      { TRACE("boolean_false_c(generate_struct_c.cc)");  return NULL;}

/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
void *generate_struct_c::visit(double_byte_character_string_c *symbol) { TRACE("double_byte_character_string_c(generate_struct_c.cc)"); return print_token(symbol);}
void *generate_struct_c::visit(single_byte_character_string_c *symbol) { TRACE("single_byte_character_string_c(generate_struct_c.cc)"); return print_token(symbol);}


/***************************/
/* B 1.2.3 - Time Literals */
/***************************/

/************************/
/* B 1.2.3.1 - Duration */
/************************/
void *generate_struct_c::visit(neg_time_c *symbol) { TRACE("neg_time_c(generate_struct_c.cc)"); return NULL;}

void *generate_struct_c::visit(duration_c *symbol) {
  TRACE("duration_c(generate_struct_c.cc)");
  if (symbol->neg != NULL)
    symbol->neg->accept(*this);
  symbol->interval->accept(*this);
  return NULL;
}

void *generate_struct_c::visit(fixed_point_c *symbol) { TRACE("fixed_point_c(generate_struct_c.cc)"); return print_token(symbol);}

/* SYM_REF5(interval_c, days, hours, minutes, seconds, milliseconds) */
void *generate_struct_c::visit(interval_c *symbol) {
    TRACE("interval_c(generate_struct_c.cc)");

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

void *generate_struct_c::visit(time_of_day_c *symbol) {
  TRACE("time_of_day_c(generate_struct_c.cc)");
  symbol->daytime->accept(*this);
  return NULL;
}

void *generate_struct_c::visit(daytime_c *symbol) {
  TRACE("daytime_c(generate_struct_c.cc)");
  symbol->day_hour->accept(*this);
  symbol->day_minute->accept(*this);
  symbol->day_second->accept(*this);
  return NULL;
}


void *generate_struct_c::visit(date_c *symbol) {
  TRACE("date_c(generate_struct_c.cc)");
  symbol->date_literal->accept(*this);
  return NULL;
}

void *generate_struct_c::visit(date_literal_c *symbol) {
  TRACE("date_literal_c(generate_struct_c.cc)");
  symbol->year->accept(*this);
  symbol->month->accept(*this);
  symbol->day->accept(*this);
  return NULL;
}

void *generate_struct_c::visit(date_and_time_c *symbol) {
  TRACE("date_and_time_c(generate_struct_c.cc)");
  symbol->date_literal->accept(*this);
  symbol->daytime->accept(*this);
  return NULL;
}



/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
void *generate_struct_c::visit(time_type_name_c *symbol)        {TRACE("time_type_name_c");  return strdup("TIME");}
void *generate_struct_c::visit(bool_type_name_c *symbol)        {TRACE("bool_type_name_c");   return strdup("BOOL");}
void *generate_struct_c::visit(sint_type_name_c *symbol)        {TRACE("sint_type_name_c");    return strdup("SINT");}
void *generate_struct_c::visit(int_type_name_c *symbol)         {TRACE("int_type_name_c");    return strdup("INT");}
void *generate_struct_c::visit(dint_type_name_c *symbol)        {TRACE("dint_type_name_c");    return strdup("DINT");}
void *generate_struct_c::visit(lint_type_name_c *symbol)        {TRACE("lint_type_name_c");     return strdup("USINT");}
void *generate_struct_c::visit(usint_type_name_c *symbol)       {TRACE("usint_type_name_c");    return strdup("USINT");}
void *generate_struct_c::visit(uint_type_name_c *symbol)        {TRACE("uint_type_name_c");      return strdup("UINT");}
void *generate_struct_c::visit(udint_type_name_c *symbol)       {TRACE("udint_type_name_c");   return strdup("UDINT");}
void *generate_struct_c::visit(ulint_type_name_c *symbol)       {TRACE("ulint_type_name_c");      return strdup("ULINT");}
void *generate_struct_c::visit(real_type_name_c *symbol)        {TRACE("real_type_name_c");   return strdup("REAL");}
void *generate_struct_c::visit(lreal_type_name_c *symbol)       {TRACE("lreal_type_name_c");  return strdup("LREAL");}
void *generate_struct_c::visit(date_type_name_c *symbol)        {TRACE("date_type_name_c");   return strdup("DATE");}
void *generate_struct_c::visit(tod_type_name_c *symbol)         {TRACE("tod_type_name_c");   return strdup("TOD");}
void *generate_struct_c::visit(dt_type_name_c *symbol)          {TRACE("dt_type_name_c");   return strdup("DT");}
void *generate_struct_c::visit(byte_type_name_c *symbol)        {TRACE("byte_type_name_c");   return strdup("BYTE");}
void *generate_struct_c::visit(word_type_name_c *symbol)        {TRACE("word_type_name_c");   return strdup("WORD");}
void *generate_struct_c::visit(lword_type_name_c *symbol)       {TRACE("lword_type_name_c");   return strdup("LWORD");}
void *generate_struct_c::visit(dword_type_name_c *symbol)       {TRACE("dword_type_name_c");   return strdup("DWORD");}
void *generate_struct_c::visit(string_type_name_c *symbol)      {TRACE("string_type_name_c");  return strdup("STRING");}
void *generate_struct_c::visit(wstring_type_name_c *symbol)     {TRACE("wstring_type_name_c");  return strdup("WSTRING");}

void *generate_struct_c::visit(safetime_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safebool_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safesint_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safeint_type_name_c *symbol)     {return NULL;}
void *generate_struct_c::visit(safedint_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safelint_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safeusint_type_name_c *symbol)   {return NULL;}
void *generate_struct_c::visit(safeuint_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safeudint_type_name_c *symbol)   {return NULL;}
void *generate_struct_c::visit(safeulint_type_name_c *symbol)   {return NULL;}
void *generate_struct_c::visit(safereal_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safelreal_type_name_c *symbol)   {return NULL;}
void *generate_struct_c::visit(safedate_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safetod_type_name_c *symbol)     {return NULL;}
void *generate_struct_c::visit(safedt_type_name_c *symbol)      {return NULL;}
void *generate_struct_c::visit(safebyte_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safeword_type_name_c *symbol)    {return NULL;}
void *generate_struct_c::visit(safelword_type_name_c *symbol)   {return NULL;}
void *generate_struct_c::visit(safedword_type_name_c *symbol)   {return NULL;}
void *generate_struct_c::visit(safestring_type_name_c *symbol)  {return NULL;}
void *generate_struct_c::visit(safewstring_type_name_c *symbol) {return NULL;}

/********************************/
/* B.1.3.2 - Generic data types */
/********************************/
void *generate_struct_c::visit(generic_type_any_c      *symbol) {TRACE("generic_type_any_c(generate_struct_c.cc)"); return NULL;}

/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
/*  TYPE type_declaration_list END_TYPE */
void *generate_struct_c::visit(data_type_declaration_c *symbol) {
  TRACE("data_type_declaration_c(generate_struct_c.cc)");

  symbol->type_declaration_list->accept(*this);

  return NULL;
}


/* helper symbol for data_type_declaration */
/*| type_declaration_list type_declaration ';' */
void *generate_struct_c::visit(type_declaration_list_c *symbol) {
  TRACE("type_declaration_list_c(generate_struct_c.cc)");
  return print_list(symbol, "", "", "");
}


/*  simple_type_name ':' simple_spec_init */
void *generate_struct_c::visit(simple_type_declaration_c *symbol) {
  TRACE("simple_type_declaration_c(generate_struct_c.cc)");
  symbol->simple_type_name->accept(*this);

  symbol->simple_spec_init->accept(*this);
  return NULL;
}


/* simple_specification ASSIGN constant */
void *generate_struct_c::visit(simple_spec_init_c *symbol) {
  TRACE("simple_spec_init_c(generate_struct_c.cc)");
#ifdef _CODE_GENERATOR
  var_type = (char*)symbol->simple_specification->accept(*this);
  if (symbol->constant != NULL) {
    var_value = (char*)symbol->constant->accept(*this);
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
void *generate_struct_c::visit(subrange_type_declaration_c *symbol) {
  TRACE("subrange_type_declaration_c(generate_struct_c.cc)");
  symbol->subrange_type_name->accept(*this);

  symbol->subrange_spec_init->accept(*this);
  return NULL;
}

/* subrange_specification ASSIGN signed_integer */
void *generate_struct_c::visit(subrange_spec_init_c *symbol) {
  TRACE("subrange_spec_init_c(generate_struct_c.cc)");
  symbol->subrange_specification->accept(*this);
  if (symbol->signed_integer != NULL) {

    symbol->signed_integer->accept(*this);
  }
  return NULL;
}

/*  integer_type_name '(' subrange')' */
void *generate_struct_c::visit(subrange_specification_c *symbol) {
  TRACE("subrange_specification_c(generate_struct_c.cc)");
  symbol->integer_type_name->accept(*this);
  if (symbol->subrange != NULL) {

    symbol->subrange->accept(*this);

  }
  return NULL;
}

/*  signed_integer DOTDOT signed_integer */
void *generate_struct_c::visit(subrange_c *symbol) {
  TRACE("subrange_c(generate_struct_c.cc)");
  symbol->lower_limit->accept(*this);

  symbol->upper_limit->accept(*this);
  return NULL;
}

/*  enumerated_type_name ':' enumerated_spec_init */
void *generate_struct_c::visit(enumerated_type_declaration_c *symbol) {
  TRACE("enumerated_type_declaration_c(generate_struct_c.cc)");
  symbol->enumerated_type_name->accept(*this);

  symbol->enumerated_spec_init->accept(*this);
  return NULL;
}

/* enumerated_specification ASSIGN enumerated_value */
void *generate_struct_c::visit(enumerated_spec_init_c *symbol) {
  TRACE("enumerated_spec_init_c(generate_struct_c.cc)");
  symbol->enumerated_specification->accept(*this);
  if (symbol->enumerated_value != NULL) {

    symbol->enumerated_value->accept(*this);
  }
  return NULL;
}

/* helper symbol for enumerated_specification->enumerated_spec_init */
/* enumerated_value_list ',' enumerated_value */
void *generate_struct_c::visit(enumerated_value_list_c *symbol) {TRACE("enumerated_value_list_c");  print_list(symbol, "(", ", ", ")"); return NULL;}

/* enumerated_type_name '#' identifier */
void *generate_struct_c::visit(enumerated_value_c *symbol) {
  TRACE("enumerated_value_c(generate_struct_c.cc)");
  if (symbol->type != NULL) {
    symbol->type->accept(*this);

  }
  symbol->value->accept(*this);
  return NULL;
}

/*  identifier ':' array_spec_init */
void *generate_struct_c::visit(array_type_declaration_c *symbol) {
  TRACE("array_type_declaration_c(generate_struct_c.cc)");
  symbol->identifier->accept(*this);

  symbol->array_spec_init->accept(*this);
  return NULL;
}

/* array_specification [ASSIGN array_initialization} */
/* array_initialization may be NULL ! */
void *generate_struct_c::visit(array_spec_init_c *symbol) {
  TRACE("array_spec_init_c(generate_struct_c.cc)");
  symbol->array_specification->accept(*this);
  if (symbol->array_initialization != NULL) {

    symbol->array_initialization->accept(*this);
  }
  return NULL;
}

/* ARRAY '[' array_subrange_list ']' OF non_generic_type_name */
void *generate_struct_c::visit(array_specification_c *symbol) {
  TRACE("array_specification_c(generate_struct_c.cc)");

  symbol->array_subrange_list->accept(*this);

  symbol->non_generic_type_name->accept(*this);
  return NULL;
}

/* helper symbol for array_specification */
/* array_subrange_list ',' subrange */
void *generate_struct_c::visit(array_subrange_list_c *symbol) { TRACE("array_subrange_list_c");  print_list(symbol, "", ", "); return NULL;}

/* helper symbol for array_initialization */
/* array_initial_elements_list ',' array_initial_elements */
void *generate_struct_c::visit(array_initial_elements_list_c *symbol) { TRACE("array_initial_elements_list_c"); print_list(symbol, "[", ", ", "]"); return NULL;}

/* integer '(' [array_initial_element] ')' */
/* array_initial_element may be NULL ! */
void *generate_struct_c::visit(array_initial_elements_c *symbol) {
  TRACE("array_initial_elements_c(generate_struct_c.cc)");
  symbol->integer->accept(*this);

  if (symbol->array_initial_element != NULL)
    symbol->array_initial_element->accept(*this);

  return NULL;
}

/*  structure_type_name ':' structure_specification */
void *generate_struct_c::visit(structure_type_declaration_c *symbol) {
  TRACE("structure_type_declaration_c(generate_struct_c.cc)");
  symbol->structure_type_name->accept(*this);

  symbol->structure_specification->accept(*this);
  return NULL;
}

/* structure_type_name ASSIGN structure_initialization */
/* structure_initialization may be NULL ! */
void *generate_struct_c::visit(initialized_structure_c *symbol) {
  TRACE("initialized_structure_c(generate_struct_c.cc)");
  var_type = (char*)symbol->structure_type_name->accept(*this);
  std::cout << "name = " << var_type << std::endl;

  if (symbol->structure_initialization != NULL) {

    symbol->structure_initialization->accept(*this);
  }
  return NULL;
}

/* helper symbol for structure_declaration */
/* structure_declaration:  STRUCT structure_element_declaration_list END_STRUCT */
/* structure_element_declaration_list structure_element_declaration ';' */
void *generate_struct_c::visit(structure_element_declaration_list_c *symbol) {
  TRACE("structure_element_declaration_list_c(generate_struct.cc)");
  print_list(symbol, "", "", "");

  return NULL;
}


void generate_struct_c::trans_struct(IValue& iv, std::string& var_type, std::string& var_value){ 
    // 数据初始值解析
    if(iv.type == TINT) {
        if (!var_value.empty())
          iv.v.value_i = std::stoi(var_value);
        struct_type->elements.push_back(iv);
    } else if(iv.type == TUINT) {
        if (!var_value.empty())
          iv.v.value_u = std::stoi(var_value);
        struct_type->elements.push_back(iv);
    } else if(iv.type == TDOUBLE) {
        if (!var_value.empty())
          iv.v.value_d = std::stod(var_value);
        struct_type->elements.push_back(iv);
    } else if(iv.type == TSTRING){
        iv.v.value_s.str = strdup(var_value.c_str());
        iv.v.value_s.length = strlen(var_value.c_str());
        struct_type->elements.push_back(iv);
    } else {
        // 结构体嵌套，待完成
        size_t i = 0; 
        std::cout << "struct cnt(generate_struct.cc) = " << structCollector.size() << std::endl;
        for(; i != structCollector.size(); ++i)
          if(var_type == structCollector[i].struct_name)
              break;
        for(size_t j = 0; j != structCollector[i].elements.size(); ++j){
           std::string tempname = iv.name;
           iv.name += structCollector[i].elements[j].name;
           iv.type = structCollector[i].elements[j].type;
           trans_struct(iv,structCollector[i].elements[j].name,var_value);
           iv.name = tempname;
        }
    }
}

/*  structure_element_name ':' *_spec_init */
void *generate_struct_c::visit(structure_element_declaration_c *symbol) {
  TRACE("structure_element_declaration_c(generate_struct.cc)");
  IValue iv; // 临时储存结构体成员
  iv.name = innerName + (char*)symbol->structure_element_name->accept(*this);

  symbol->spec_init->accept(*this);

  // std::cout << "****** teststr = " << teststr << std::endl;
  std::cout << var_type << " " << var_value << std::endl;

    if((iv.type = pre_generate_pou_info_c::variable_type_check(var_type)) == TUNDEF){
       ERROR_MSG("variable type check error!");
    }
    // trans_struct(iv,var_type,var_value);
    // 数据初始值解析
    if(iv.type == TINT) {
        if (!var_value.empty())
          iv.v.value_i = std::stoi(var_value);
        struct_type->elements.push_back(iv);
    } else if(iv.type == TUINT) {
        if (!var_value.empty())
          iv.v.value_u = std::stoi(var_value);
        struct_type->elements.push_back(iv);
    } else if(iv.type == TDOUBLE) {
        if (!var_value.empty())
          iv.v.value_d = std::stod(var_value);
        struct_type->elements.push_back(iv);
    } else if(iv.type == TSTRING){
        iv.v.value_s.str = strdup(var_value.c_str());
        iv.v.value_s.length = strlen(var_value.c_str());
        struct_type->elements.push_back(iv);
    } else {
        // 结构体嵌套，待完成
        iv.v.value_p.ref_type = strdup(var_type.c_str());  // 具体的复合数据类型
        innerName = iv.name;
        type_symtable[var_type]->accept(*this);

          //iv.v.value_p.value_index = std::stoi(var_value);//var_value; // 具体值
    }
  // struct_type->elements.push_back(iv);

  return NULL;
}

/* helper symbol for structure_initialization */
/* structure_initialization: '(' structure_element_initialization_list ')' */
/* structure_element_initialization_list ',' structure_element_initialization */
void *generate_struct_c::visit(structure_element_initialization_list_c *symbol) {TRACE("structure_element_initialization_list_c"); print_list(symbol, "(", ", ", ")"); return NULL;}

/*  structure_element_name ASSIGN value */
void *generate_struct_c::visit(structure_element_initialization_c *symbol) {
  TRACE("structure_element_initialization_c(generate_struct_c.cc)");
  symbol->structure_element_name->accept(*this);

  symbol->value->accept(*this);
  return NULL;
}

/*  string_type_name ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init */
void *generate_struct_c::visit(string_type_declaration_c *symbol) {
  TRACE("string_type_declaration_c(generate_struct_c.cc)");
  symbol->string_type_name->accept(*this);

  symbol->elementary_string_type_name->accept(*this);
  symbol->string_type_declaration_size->accept(*this);
  if (symbol->string_type_declaration_init != NULL)
    symbol->string_type_declaration_init->accept(*this);
  return NULL;
}

/*  function_block_type_name ASSIGN structure_initialization */
/* structure_initialization -> may be NULL ! */
void *generate_struct_c::visit(fb_spec_init_c *symbol) {
  TRACE("fb_spec_init_c(generate_struct_c.cc)");
  symbol->function_block_type_name->accept(*this);
  if (symbol->structure_initialization != NULL) {

    symbol->structure_initialization->accept(*this);
  }
  return NULL;
}



/* ref_spec:  REF_TO (non_generic_type_name | function_block_type_name) */
// SYM_REF1(ref_spec_c, type_name)
void *generate_struct_c::visit(ref_spec_c *symbol) {
  TRACE("ref_spec_c(generate_struct_c.cc)");

  symbol->type_name->accept(*this);
  return NULL;
}

/* For the moment, we do not support initialising reference data types */
/* ref_spec_init: ref_spec [ ASSIGN ref_initialization ]; */
/* NOTE: ref_initialization may be NULL!! */
// SYM_REF2(ref_spec_init_c, ref_spec, ref_initialization)
void *generate_struct_c::visit(ref_spec_init_c *symbol) {
  TRACE("ref_spec_init_c(generate_struct_c.cc)");
  symbol->ref_spec->accept(*this);
  if (symbol->ref_initialization != NULL) {

    symbol->ref_initialization->accept(*this);
  }
  return NULL;
}

/* ref_type_decl: identifier ':' ref_spec_init */
// SYM_REF2(ref_type_decl_c, ref_type_name, ref_spec_init)
void *generate_struct_c::visit(ref_type_decl_c *symbol) {
  TRACE("ref_type_decl_c(generate_struct_c.cc)");
  symbol->ref_type_name->accept(*this);
  symbol->ref_spec_init->accept(*this);
  return NULL;
}



/*********************/
/* B 1.4 - Variables */
/*********************/
void *generate_struct_c::visit(symbolic_variable_c *symbol) {
	TRACE("symbolic_variable_c(generate_struct_c.cc)");
	int temp_num;
	std::string temp_num_str;
	std::string temp_str;

	temp_str = (char*)symbol->var_name->accept(*this);

	temp_num_str = utility_token_get_c::numeric_to_string(temp_num);

	return strdup(temp_num_str.c_str());
}


void *generate_struct_c::visit(symbolic_constant_c *symbol) {TRACE("symbolic_constant_c(generate_struct_c.cc)"); return symbol->var_name->accept(*this);}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *generate_struct_c::visit(direct_variable_c *symbol) {TRACE("direct_variable_c(generate_struct_c.cc)"); return NULL;}


/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
void *generate_struct_c::visit(array_variable_c *symbol) {
  TRACE("array_variable_c(generate_struct_c.cc)");
  symbol->subscripted_variable->accept(*this);
  symbol->subscript_list->accept(*this);
  return NULL;
}


/* subscript_list ',' subscript */
void *generate_struct_c::visit(subscript_list_c *symbol) {TRACE("subscript_list_c(generate_struct_c.cc)"); return NULL; }

/*  record_variable '.' field_selector */
void *generate_struct_c::visit(structured_variable_c *symbol) {
  TRACE("structured_variable_c(generate_struct_c.cc)");
  symbol->record_variable->accept(*this);
  symbol->field_selector->accept(*this);
  return NULL;
}
