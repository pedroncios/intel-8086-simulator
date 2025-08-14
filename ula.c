#include "simulador.h"

union tagRegistrator
{
	long Reg32;
	short int Reg16[2];
};

////////////////////////////////////////////////////////


void ULA(char *inst, int *op1, int *op2, char *reg1, char *reg2, int tipo)
{
	union tagRegistrator RegMul;
	union tagRegistrator RegDiv;
	int result=0, tmp=0;

	unsigned char uc; //MUL
	unsigned char u8; //DIV
	unsigned short int u16; //DIV
	signed char sc; //IMUL
	signed char s8; //IDIV
	signed short int s16; //IDIV

	/* ADDRM */
	if( strcmpi(inst, "addrm") == 0 )
	{
		// // calcula para poder passar como parametro o result para teste de flags
		if(tipo == 8)
		{
			result = *reg1 + *op2;
			op1 = reg1;
			TestaFlags_8Bits(*op1, *op2, result);
			
			aBus = *reg1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 + tmp2;
			*reg1 = aBus;
		}
		else if(tipo == 16)
		{
			result = *op1 + *op2;
			TestaFlags_16Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 + tmp2;
			*op1 = aBus;
		}
	}
	/* ADDMR */
	else if( strcmpi(inst, "addmr") == 0 )
	{
		// // calcula para poder passar como parametro o result para teste de flags
		if(tipo == 8)
		{
			result = *op1 + *reg2;
			op2 = reg2;
			TestaFlags_8Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *reg2;
			tmp2 = aBus;

			aBus = tmp1 + tmp2;
			*op1 = aBus;
		}
		else if(tipo == 16)
		{
			result = *op1 + *op2;
			TestaFlags_16Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 + tmp2;
			*op1 = aBus;
		}
	}
	/* ADDRR */
	else if( strcmpi(inst, "addrr") == 0 )
	{
		// // calcula para poder passar como parametro o result para teste de flags
		if(tipo == 8)
		{
			result = *reg1 + *reg2;
			op1 = reg1;
			op2 = reg2;
			TestaFlags_8Bits(*op1, *op2, result);
			
			aBus = *reg1;
			tmp1 = aBus;
			aBus = *reg2;
			tmp2 = aBus;

			aBus = tmp1 + tmp2;
			*reg1 = aBus;
		}
		else if(tipo == 16)
		{
			result = *op1 + *op2;
			TestaFlags_16Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 + tmp2;
			*op1 = aBus;
		}
	}
	/* ADDMI */
	else if( strcmpi(inst, "addmi") == 0 )
	{
		result = *op1 + *op2;
		if(tipo == 8)			
			TestaFlags_8Bits(*op1, *op2, result);

		else if(tipo == 16)
			TestaFlags_16Bits(*op1, *op2, result);
			
		aBus = *op1;
		tmp1 = aBus;
		aBus = *op2;
		tmp2 = aBus;

		aBus = tmp1 + tmp2;
		*op1 = aBus;
	}

	/* ADDRI */
	else if( strcmpi(inst, "addri") == 0 )
	{
		if(tipo == 8)
		{
			result = *reg1 + *op2;
			op1 = reg1;
			TestaFlags_8Bits(*op1, *op2, result);
			
			aBus = *reg1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 + tmp2;
			*reg1 = aBus;
		}
		else if(tipo == 16)
		{
			result = *op1 + *op2;
			TestaFlags_16Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 + tmp2;
			*op1 = aBus;
		}
	}

	/* SUBRM */
	else if( strcmpi(inst, "subrm") == 0 )
	{
		if(tipo == 8)
		{
			result = *reg1 - *op2;
			op1 = reg1;
			TestaFlags_8Bits(*op1, *op2, result);
			
			aBus = *reg1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*reg1 = aBus;
		}
		else if(tipo == 16)
		{
			result = *op1 - *op2;
			TestaFlags_16Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*op1 = aBus;
		}
	}

	/* SUBMR */
	else if( strcmpi(inst, "submr") == 0 )
	{
		if(tipo == 8)
		{
			result = *op1 - *reg2;
			op2 = reg2;
			TestaFlags_8Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *reg2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*op1 = aBus;
		}
		else if(tipo == 16)
		{
			result = *op1 - *op2;
			TestaFlags_16Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*op1 = aBus;
		}
	}

	/* SUBRR */
	else if( strcmpi(inst, "subrr") == 0 )
	{
		if(tipo == 8)
		{
			result = *reg1 - *reg2;
			op1 = reg1;
			op2 = reg2;
			TestaFlags_8Bits(*op1, *op2, result);
			
			aBus = *reg1;
			tmp1 = aBus;
			aBus = *reg2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*reg1 = aBus;
		}
		else if(tipo == 16)
		{
			result = *op1 - *op2;
			TestaFlags_16Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*op1 = aBus;
		}
	}

	/* SUBMI */
	else if( strcmpi(inst, "submi") == 0 )
	{
		if(tipo == 8)
		{
			result = *op1 - *op2;
			TestaFlags_8Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*op1 = aBus;
		}
		else if(tipo == 16)
		{
			result = *op1 - *op2;
			TestaFlags_16Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*op1 = aBus;
		}
	}

	/* SUBRI */
	else if( strcmpi(inst, "subri") == 0 )
	{
		if(tipo == 8)
		{
			result = *reg1 - *op2;
			op1 = reg1;
			TestaFlags_8Bits(*op1, *op2, result);
			
			aBus = *reg1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*reg1 = aBus;
		}
		else if(tipo == 16)
		{
			result = *op1 - *op2;
			TestaFlags_16Bits(*op1, *op2, result);
			
			aBus = *op1;
			tmp1 = aBus;
			aBus = *op2;
			tmp2 = aBus;

			aBus = tmp1 - tmp2;
			*op1 = aBus;
		}
	}

	/* MULR */
	else if( strcmpi(inst, "mulr") == 0)
	{
		if(tipo == 8)
		{
			aBus = *reg1;
			tmp1 = aBus;

			aBus = AX.Reg8[AL] * tmp1;
			AX.Reg16 = aBus;
			
			result = aBus;
			if( result < -32768 || result > 32767 )
				OV = 1;
			else if(result > 65535)
				CF = 1;
		}
		else if( tipo == 16 )
		{
			aBus = *op1;
			tmp1 = aBus;

			RegMul.Reg32 = AX.Reg16 * tmp1;

			aBus = RegMul.Reg16[0]; // Parte Baixa
			/*AX Parte Baixa*/AX.Reg16 = aBus;

			aBus = RegMul.Reg16[1]; // Parte Alta
			/*BX Parte Alta*/BX.Reg16 = aBus;
			
			uc = BX.Reg8[BL];
			if( uc > 0 )
				CF = OV = 1;
		}
	}
	/* MULM */
	else if( strcmpi(inst, "mulm") == 0)
	{
		if(tipo == 8)
		{
			aBus = *op1;
			tmp1 = aBus;

			aBus = AX.Reg8[AL] * tmp1;
			AX.Reg16 = aBus;
			
			result = aBus;
			if( result < -32768 || result > 32767 )
				OV = 1;
			else if(result > 65535)
				CF = 1;
		}
		else if( tipo == 16 )
		{
			aBus = *op1;
			tmp1 = aBus;

			RegMul.Reg32 = AX.Reg16 * tmp1;

			aBus = RegMul.Reg16[0]; // Parte Baixa
			/*AX Parte Baixa*/AX.Reg16 = aBus;

			aBus = RegMul.Reg16[1]; // Parte Alta
			/*BX Parte Alta*/BX.Reg16 = aBus;
			
			uc = BX.Reg8[BL];
			if( uc > 0 )
				CF = OV = 1;
		}
	}

	/* DIVR */
	else if( strcmpi(inst, "divr") == 0)
	{
		// 8 bits: AL(quociente) e AH(resto)
		// 16 bits: AX(") e BX(")
		if(tipo == 8)
		{
			aBus = *reg1;
			tmp1 = aBus;

			u8 = tmp1;			
			tmp1 = AX.Reg16 / u8;
			aBus = AX.Reg16 % u8;

			/*AL*/AX.Reg8[AL] = tmp1;
			/*AH*/AX.Reg8[AH] = aBus;
		}
		else if( tipo == 16 )
		{
			aBus = *op1;
			tmp1 = aBus;
			
			RegDiv.Reg16[0] = AX.Reg16; //Parte Baixa
			RegDiv.Reg16[1] = BX.Reg16; //Parte Alta

			u16 = tmp1;
			aBus = RegDiv.Reg32 / u16;
			/*AX*/AX.Reg16 = aBus;
			
			aBus = RegDiv.Reg32 % u16;
			/*BX*/BX.Reg16 = aBus;
		}	
	}
	/* DIVM */
	else if( strcmpi(inst, "divm") == 0)
	{
		// 8 bits: AL(quociente) e AH(resto)
		// 16 bits: AX(") e BX(")
		if(tipo == 8)
		{
			aBus = *op1;
			tmp1 = aBus;
			
			u8 = tmp1;
			aBus = AX.Reg16 / u8;
			/*AL*/AX.Reg8[AL] = aBus;
			
			aBus = AX.Reg16 % u8;
			/*AH*/AX.Reg8[AH] = aBus;
		}
		else if( tipo == 16 )
		{
			aBus = *op1;
			tmp1 = aBus;
			
			RegDiv.Reg16[0] = AX.Reg16; //Parte Baixa
			RegDiv.Reg16[1] = BX.Reg16; //Parte Alta

			u16 = tmp1;
			aBus = RegDiv.Reg32 / u16;
			/*AX*/AX.Reg16 = aBus;
			
			aBus = RegDiv.Reg32 % u16;
			/*BX*/BX.Reg16 = aBus;
		}	
	}


	/* IMULR */
	else if( strcmpi(inst, "imulr") == 0 )
	{
		if(tipo == 8)
		{
			aBus = *reg1;
			tmp1 = aBus;

			aBus = AX.Reg8[AL] * tmp1;
			AX.Reg16 = aBus;
			
			result = aBus;
			if( result < -32768 || (result > 32767 && result < 65535))
				OV = 1;
			else if( result < -32768 || (result > 32767 && result > 65535))
				CF = 1;
		}
		else if( tipo == 16 )
		{
			aBus = *op1;
			tmp1 = aBus;

			RegMul.Reg32 = AX.Reg16 * tmp1;

			aBus = RegMul.Reg16[0]; // Parte Baixa
			/*AX Parte Baixa*/AX.Reg16 = aBus;

			aBus = RegMul.Reg16[1]; // Parte Alta
			/*BX Parte Alta*/BX.Reg16 = aBus;
			
			sc = BX.Reg8[BL];
			if( sc > 0 )
				CF = OV = 1;
		}
	}
	/* IMULM */
	else if( strcmpi(inst, "imulm") == 0 )
	{
		if(tipo == 8)
		{
			aBus = *op1;
			tmp1 = aBus;

			aBus = AX.Reg8[AL] * tmp1;
			AX.Reg16 = aBus;
			
			result = aBus;
			if( result < -32768 || (result > 32767 && result < 65535))
				OV = 1;
			else if( result < -32768 || (result > 32767 && result > 65535))
				CF = 1;
		}
		else if( tipo == 16 )
		{
			aBus = *op1;
			tmp1 = aBus;

			RegMul.Reg32 = AX.Reg16 * tmp1;

			aBus = RegMul.Reg16[0]; // Parte Baixa
			/*AX Parte Baixa*/AX.Reg16 = aBus;

			aBus = RegMul.Reg16[1]; // Parte Alta
			/*BX Parte Alta*/BX.Reg16 = aBus;
			
			sc = BX.Reg8[BL];
			if( sc > 0 )
				CF = OV = 1;
		}
	}

	/* IDIVR */
	else if( strcmpi(inst, "idivr") == 0)
	{
		if(tipo == 8)
		{
			aBus = *reg1;
			tmp1 = aBus;
			
			aBus = AX.Reg16 / tmp1;
			/*AL*/AX.Reg8[AL] = aBus;
			
			s8 = tmp1;
			aBus = AX.Reg16 % s8;
			/*AH*/AX.Reg8[AH] = aBus;
		}
		else if( tipo == 16 )
		{
			aBus = *op1;
			tmp1 = aBus;
			
			RegDiv.Reg16[0] = AX.Reg16; //Parte Baixa
			RegDiv.Reg16[1] = BX.Reg16; //Parte Alta

			s16 = tmp1;
			aBus = RegDiv.Reg32 / s16;
			/*AX*/AX.Reg16 = aBus;
			
			aBus = RegDiv.Reg32 % s16;
			/*BX*/BX.Reg16 = aBus;
		}	
	}
	/* IDIVM */
	else if( strcmpi(inst, "idivm") == 0)
	{
		if(tipo == 8)
		{
			aBus = *op1;
			tmp1 = aBus;

			s8 = tmp1;			
			aBus = AX.Reg16 / s8;
			/*AL*/AX.Reg8[AL] = aBus;
			
			aBus = AX.Reg16 % s8;
			/*AH*/AX.Reg8[AH] = aBus;
		}
		else if( tipo == 16 )
		{
			aBus = *op1;
			tmp1 = aBus;
			
			RegDiv.Reg16[0] = AX.Reg16; //Parte Baixa
			RegDiv.Reg16[1] = BX.Reg16; //Parte Alta

			s16 = tmp1;
			aBus = RegDiv.Reg32 / s16;
			/*AX*/AX.Reg16 = aBus;
			
			aBus = RegDiv.Reg32 % s16;
			/*BX*/BX.Reg16 = aBus;
		}	
	}

	/* CMP */
	else if( strcmpi(inst, "cmprm") == 0 || strcmpi(inst, "cmpmr") == 0 || strcmpi(inst, "cmprr") == 0 || strcmpi(inst, "cmpmi") == 0 || strcmpi(inst, "cmpri") == 0 )
	{
		if(inst[3] == 'r' || inst[3] == 'R')
		{
			if(tipo == 8)
				aBus = *reg1;
			else //tipo == 16
				aBus = *op1;
		}
		else
			aBus = *op1;

		tmp1 = aBus;
		
		if(inst[4] == 'r'  || inst[4] == 'R')
		{
			if(tipo == 8)
				aBus = *reg2;
			else //tipo == 16
				aBus = *op2;
		}
		else
			aBus = *op2;

		tmp2 = aBus;

		result = tmp1 - tmp2;

		OV = SF = CF = ZF = 0;

		if(tipo == 8)
			TestaFlags_8Bits(tmp1, tmp2, result);

		else if(tipo == 16)
			TestaFlags_16Bits(tmp1, tmp2, result);

		/*OV = SF = CF = ZF = 0;

		if( tmp1 > tmp2 )
		{
			CF = 0;
			ZF = 0;
		}
		if( tmp1 == tmp2 )
			ZF = 1;

		if( tmp1 < tmp2 )
		{
			CF = 1;
			SF = 1;
		}*/
	}

	/* AND */
	else if( strcmpi(inst, "andrm") == 0 || strcmpi(inst, "andmr") == 0 || strcmpi(inst, "andrr") == 0 || strcmpi(inst, "andmi") == 0 || strcmpi(inst, "andri") == 0 )
	{
		if(inst[3] == 'r' || inst[3] == 'R')
		{
			if(tipo == 8)
				aBus = *reg1;
			else //tipo == 16
				aBus = *op1;
		}
		else
			aBus = *op1;

		tmp1 = aBus;
		
		if(inst[4] == 'r'  || inst[4] == 'R')
		{
			if(tipo == 8)
				aBus = *reg2;
			else //tipo == 16
				aBus = *op2;
		}
		else
			aBus = *op2;

		tmp2 = aBus;

		aBus = tmp1 & tmp2;
		
		if(inst[3] == 'r' || inst[3] == 'R')
		{
			if(tipo == 8)
				*reg1 = aBus;
			else //tipo == 16
				*op1 = aBus;
		}
		else
			*op1 = aBus;

		result = aBus;

		// SF flag
		tmp = result & 0x80;
		if( tmp > 0 )
			SF = 1;

		// ZF flag
		if( result == 0 ) // 256 devido ao estouro do 255 q volta e vira 0
			ZF = 1;
	}

	/* OR */
	else if( strcmpi(inst, "orrm") == 0 || strcmpi(inst, "ormr") == 0 || strcmpi(inst, "orrr") == 0 || strcmpi(inst, "ormi") == 0 || strcmpi(inst, "orri") == 0 )
	{
		if(inst[2] == 'r' || inst[2] == 'R')
		{
			if(tipo == 8)
				aBus = *reg1;
			else //tipo == 16
				aBus = *op1;
		}
		else
			aBus = *op1;

		tmp1 = aBus;
		
		if(inst[3] == 'r'  || inst[3] == 'R')
		{
			if(tipo == 8)
				aBus = *reg2;
			else //tipo == 16
				aBus = *op2;
		}
		else
			aBus = *op2;

		tmp2 = aBus;

		aBus = tmp1 | tmp2;
		
		if(inst[2] == 'r' || inst[2] == 'R')
		{
			if(tipo == 8)
				*reg1 = aBus;
			else //tipo == 16
				*op1 = aBus;
		}
		else
			*op1 = aBus;

		result = aBus;

		// SF flag
		tmp = result & 0x80;
		if( tmp > 0 )
			SF = 1;

		// ZF flag
		if( result == 0 ) // 256 devido ao estouro do 255 q volta e vira 0
			ZF = 1;
	}

	/* XOR */
	else if( strcmpi(inst, "xorrm") == 0 || strcmpi(inst, "xormr") == 0 || strcmpi(inst, "xorrr") == 0 || strcmpi(inst, "xormi") == 0 || strcmpi(inst, "xorri") == 0 )
	{
		if(inst[3] == 'r' || inst[3] == 'R')
		{
			if(tipo == 8)
				aBus = *reg1;
			else //tipo == 16
				aBus = *op1;
		}
		else
			aBus = *op1;

		tmp1 = aBus;
		
		if(inst[4] == 'r'  || inst[4] == 'R')
		{
			if(tipo == 8)
				aBus = *reg2;
			else //tipo == 16
				aBus = *op2;
		}
		else
			aBus = *op2;

		tmp2 = aBus;
		

		aBus = tmp1 ^ tmp2;

		if(inst[3] == 'r' || inst[3] == 'R')
		{
			if(tipo == 8)
				*reg1 = aBus;
			else //tipo == 16
				*op1 = aBus;
		}
		else
			*op1 = aBus;

		result = aBus;

		// SF flag
		tmp = result & 0x80;
		if( tmp > 0 )
			SF = 1;

		// ZF flag
		if( result == 0 ) // 256 devido ao estouro do 255 q volta e vira 0
			ZF = 1;
	}

	/* NOT */
	else if( strcmpi(inst, "notm") == 0 || strcmpi(inst, "notr") == 0 )
	{
		if(inst[3] == 'r' || inst[3] == 'R')
		{
			if(tipo == 8)
				*reg1 = ~*reg1;
			else //tipo == 16
				*op1 = ~*op1;
		}
		else //
			*op1 = ~*op1;
	}                                                                                                                                                                                                                                        
}

// Sub e Add
int TestaFlags_8Bits(int op1, int op2, int result)
{
	int tmp;

	// SF flag
	tmp = result & 0x80;
	if( tmp > 0 )
		SF = 1;

	// OV flag
	if( result < -128 || result > 127 )
		OV = 1;

	// ZF flag
	if( result == 0 || result == 256 ) // 256 devido ao estouro do 255 q volta e vira 0
		ZF = 1;

	// CF flag
	tmp = result & 0xFF00;
	if( tmp > 0 || (op1 > 0 && op2 < 0 && result > 127))
		CF = 1;

	return 0;
}

// Sub e Add
int TestaFlags_16Bits(int op1, int op2, int result)
{
	int tmp;

	// SF flag
	tmp = result & 0x8000;
	if( tmp > 0 )
		SF = 1;

	// OV flag
	if( result < -32761 || result > 32767 )
		OV = 1;

	// ZF flag
	if( result == 0 )
		ZF = 1;

	// CF flag
	tmp = result & 0xFFFF0000;
	if( tmp > 0 )
		CF = 1;

	return 0;
}