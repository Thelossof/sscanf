#include "utils.h"
#include "errors.h"

error_t
	Utils::
	ReadOctal(char const * & input, cell & n)
{
	n = 0;
	if (*input == '\0') return ERROR_NAN;
	if ('0' <= *input && *input <= '7')
	{
		do
		{
			n = n * 8 + (*input++ - '0');
		}
		while ('0' <= *input && *input <= '7');
	}
	else return ERROR_NAN;
	return OK;
}

// Test valid formats.
TEST(Oct0,  { cell n; return Utils::ReadOctal(S"0", n) == OK && n == 0; })
TEST(Oct1,  { cell n; return Utils::ReadOctal(S"066", n) == OK && n == 066; })
TEST(Oct2,  { cell n; return Utils::ReadOctal(S"088", n) == OK && n == 0; })
TEST(Oct4,  { cell n; return Utils::ReadOctal(S"01234", n) == OK && n == 01234; })
TEST(Oct6,  { cell n; return Utils::ReadOctal(S"5k", n) == OK && n == 05; })
TEST(Oct7,  { cell n; return Utils::ReadOctal(S"7|", n) == OK && n == 07; })
TEST(Oct8,  { cell n; return Utils::ReadOctal(S"0044(", n) == OK && n == 044; })
// Test fails.
TEST(Oct5,  { cell n; return Utils::ReadOctal(S"-0", n) == ERROR_NAN; })
TEST(Oct3,  { cell n; return Utils::ReadOctal(S"99", n) == ERROR_NAN; })
TEST(Oct9,  { cell n; return Utils::ReadOctal(S"(3)", n) == ERROR_NAN; })
TEST(Oct10, { cell n; return Utils::ReadOctal(S"", n) == ERROR_NAN; })

error_t
	Utils::
	ReadDecimal(char const * & input, cell & n)
{
	bool
		neg = false;
	n = 0;
	if (*input == '\0') return ERROR_NAN;
	else if (*input == '-')
	{
		neg = true;
		++input;
	}
	if ('0' <= *input && *input <= '9')
	{
		do
		{
			n = n * 10 + (*input++ - '0');
		}
		while ('0' <= *input && *input <= '9');
	}
	else return ERROR_NAN;
	if (neg) n = -n;
	return OK;
}

// Test valid formats.
TEST(Dec0,  { cell n; return Utils::ReadDecimal(S"0", n) == OK && n == 0; })
TEST(Dec1,  { cell n; return Utils::ReadDecimal(S"24", n) == OK && n == 24; })
TEST(Dec1c, { cell n; return Utils::ReadDecimal(S"-55", n) == OK && n == -55; })
TEST(Dec1d, { cell n; return Utils::ReadDecimal(S"-193", n) == OK && n == -193; })
TEST(Dec1e, { cell n; return Utils::ReadDecimal(S"-067", n) == OK && n == -67; })
TEST(Dec5b, { cell n; return Utils::ReadDecimal(S"0000088", n) == OK && n == 88; })
// Test ends.
TEST(Dec6,  { cell n; return Utils::ReadDecimal(S"7!", n) == OK && n == 7; })
TEST(Dec7,  { cell n; return Utils::ReadDecimal(S"6)", n) == OK && n == 6; })
TEST(Dec8,  { cell n; return Utils::ReadDecimal(S"5G", n) == OK && n == 5; })
// Test not hex.
TEST(Dec2,  { cell n; return Utils::ReadDecimal(S"0x1", n) == OK && n == 0; })
TEST(Dec3,  { cell n; return Utils::ReadDecimal(S"FF", n) == ERROR_NAN; })
TEST(Dec4,  { cell n; return Utils::ReadDecimal(S"5C", n) == OK && n == 5; })
// Test invalid formats.
TEST(Dec9,  { cell n; return Utils::ReadDecimal(S"q", n) == ERROR_NAN; })
TEST(Dec10, { cell n; return Utils::ReadDecimal(S"(6)", n) == ERROR_NAN; })
TEST(Dec12, { cell n; return Utils::ReadDecimal(S"!", n) == ERROR_NAN; })
TEST(Dec17, { cell n; return Utils::ReadDecimal(S"-", n) == ERROR_NAN; })
TEST(Dec18, { cell n; return Utils::ReadDecimal(S"", n) == ERROR_NAN; })
// Test all digits.
TEST(Dec13, { cell n; return Utils::ReadDecimal(S"123", n) == OK && n == 123; })
TEST(Dec14, { cell n; return Utils::ReadDecimal(S"456", n) == OK && n == 456; })
TEST(Dec15, { cell n; return Utils::ReadDecimal(S"789", n) == OK && n == 789; })
TEST(Dec16, { cell n; return Utils::ReadDecimal(S"-0", n) == OK && n == 0; })

cell
	GetHexCharacter(char const c)
{
	return
		('0' <= c && c <= '9') ? (c - '0') : (
		('a' <= c && c <= 'f') ? (c - 'a' + 10) : (
		('A' <= c && c <= 'F') ? (c - 'A' + 10) : (
		(-1))));
}

// Tests.
TEST(HexChar0, { return GetHexCharacter('0') == 0; })
TEST(HexChar1, { return GetHexCharacter('1') == 1; })
TEST(HexChar2, { return GetHexCharacter('2') == 2; })
TEST(HexChar3, { return GetHexCharacter('3') == 3; })
TEST(HexChar4, { return GetHexCharacter('4') == 4; })
TEST(HexChar5, { return GetHexCharacter('5') == 5; })
TEST(HexChar6, { return GetHexCharacter('6') == 6; })
TEST(HexChar7, { return GetHexCharacter('7') == 7; })
TEST(HexChar8, { return GetHexCharacter('8') == 8; })
TEST(HexChar9, { return GetHexCharacter('9') == 9; })
TEST(HexChara, { return GetHexCharacter('a') == 10; })
TEST(HexCharb, { return GetHexCharacter('b') == 11; })
TEST(HexCharc, { return GetHexCharacter('c') == 12; })
TEST(HexChard, { return GetHexCharacter('d') == 13; })
TEST(HexChare, { return GetHexCharacter('e') == 14; })
TEST(HexCharf, { return GetHexCharacter('f') == 15; })
TEST(HexCharA, { return GetHexCharacter('A') == 10; })
TEST(HexCharB, { return GetHexCharacter('B') == 11; })
TEST(HexCharC, { return GetHexCharacter('C') == 12; })
TEST(HexCharD, { return GetHexCharacter('D') == 13; })
TEST(HexCharE, { return GetHexCharacter('E') == 14; })
TEST(HexCharF, { return GetHexCharacter('F') == 15; })
TEST(HexCharg, { return GetHexCharacter('g') == -1; })
TEST(HexCharG, { return GetHexCharacter('G') == -1; })
TEST(HexCharo0, { return GetHexCharacter('\0') == -1; })
TEST(HexCharo1, { return GetHexCharacter('\\') == -1; })
TEST(HexCharo2, { return GetHexCharacter('z') == -1; })
TEST(HexCharo3, { return GetHexCharacter(':') == -1; })

error_t
	Utils::
	ReadHex(char const * & input, cell & n)
{
	cell
		cur;
	n = 0;
	if (*input == '\0') return ERROR_NAN;
	else if (*input == '0')
	{
		++input;
		if (*input == 'x' || *input == 'X')
		{
			++input;
		}
		else if (GetHexCharacter(*input) == -1) return OK;
	}
	if ((cur = GetHexCharacter(*input++)) == -1) return ERROR_NAN;
	else
	{
		do
		{
			n = n * 16 + cur;
		}
		while ((cur = GetHexCharacter(*input++)) != -1);
	}
	--input;
	return OK;
}

// Test valid formats.
TEST(Hex0,  { cell n; return Utils::ReadHex(S"0", n) == OK && n == 0; })
TEST(Hex1,  { cell n; return Utils::ReadHex(S"24", n) == OK && n == 0x24; })
TEST(Hex2,  { cell n; return Utils::ReadHex(S"0x24", n) == OK && n == 0x24; })
TEST(Hex3,  { cell n; return Utils::ReadHex(S"0X24", n) == OK && n == 0x24; })
TEST(Hex4a, { cell n; return Utils::ReadHex(S"2f", n) == OK && n == 0x2F; })
TEST(Hex4b, { cell n; return Utils::ReadHex(S"2F", n) == OK && n == 0x2f; })
TEST(Hex5a, { cell n; return Utils::ReadHex(S"0x000088", n) == OK && n == 0x88; })
TEST(Hex5b, { cell n; return Utils::ReadHex(S"0000088", n) == OK && n == 0x88; })
TEST(Hex5c, { cell n; return Utils::ReadHex(S"00000x88", n) == OK && n == 0; })
TEST(Hex5d, { cell n; return Utils::ReadHex(S"000x88", n) == OK && n == 0; })
TEST(Hex5e, { cell n; return Utils::ReadHex(S"0X88", n) == OK && n == 0x88; })
// Test ends.
TEST(Hex6,  { cell n; return Utils::ReadHex(S"E!", n) == OK && n == 0xE; })
TEST(Hex7,  { cell n; return Utils::ReadHex(S"B)", n) == OK && n == 0xB; })
TEST(Hex8,  { cell n; return Utils::ReadHex(S"CG", n) == OK && n == 0xC; })
// Test invalid formats.
TEST(Hex9,  { cell n; return Utils::ReadHex(S"G", n) == ERROR_NAN; })
TEST(Hex10, { cell n; return Utils::ReadHex(S"(6)", n) == ERROR_NAN; })
TEST(Hex11, { cell n; return Utils::ReadHex(S"-8", n) == ERROR_NAN; })
TEST(Hex12, { cell n; return Utils::ReadHex(S"", n) == ERROR_NAN; })
// Test all digits.
TEST(Hex13, { cell n; return Utils::ReadHex(S"0x123", n) == OK && n == 0x123; })
TEST(Hex14, { cell n; return Utils::ReadHex(S"0x456", n) == OK && n == 0x456; })
TEST(Hex15, { cell n; return Utils::ReadHex(S"0x789", n) == OK && n == 0x789; })
TEST(Hex16, { cell n; return Utils::ReadHex(S"0x0AB", n) == OK && n == 0x0AB; })
TEST(Hex17, { cell n; return Utils::ReadHex(S"0xCDE", n) == OK && n == 0xCDE; })
TEST(Hex18, { cell n; return Utils::ReadHex(S"0xFab", n) == OK && n == 0xFab; })
TEST(Hex19, { cell n; return Utils::ReadHex(S"0xcde", n) == OK && n == 0xcde; })
TEST(Hex20, { cell n; return Utils::ReadHex(S"0xf77", n) == OK && n == 0xf77; })

error_t
	Utils::
	ReadBinary(char const * & input, cell & n)
{
	n = 0;
	if (*input == '\0') return ERROR_NAN;
	else if (*input == '0')
	{
		++input;
		if (*input == 'b' || *input == 'B')
		{
			++input;
		}
		else if (*input != '0' && *input != '1') return OK;
	}
	if (*input == '0' || *input == '1')
	{
		for ( ; ; )
		{
			switch (*input)
			{
				case '0':
					n <<= 1;
					break;
				case '1':
					n = (n << 1) | 1;
					break;
				default:
					return OK;
			}
			++input;
		}
	}
	return ERROR_NAN;
}

// Test valid formats (annoyingly, C doesn't support 0b0 syntax).
TEST(Bin0,  { cell n; return Utils::ReadBinary(S"0", n) == OK && n == 0; })
TEST(Bin1,  { cell n; return Utils::ReadBinary(S"1", n) == OK && n == 1; })
TEST(Bin2,  { cell n; return Utils::ReadBinary(S"010101", n) == OK && n == 21; })
TEST(Bin3,  { cell n; return Utils::ReadBinary(S"111000", n) == OK && n == 56; })
TEST(Bin4a, { cell n; return Utils::ReadBinary(S"0b000111", n) == OK && n == 7; })
TEST(Bin4b, { cell n; return Utils::ReadBinary(S"0B11", n) == OK && n == 3; })
TEST(Bin5a, { cell n; return Utils::ReadBinary(S"10121", n) == OK && n == 5; })
// Test ends.
TEST(Bin6,  { cell n; return Utils::ReadBinary(S"1100!", n) == OK && n == 12; })
TEST(Bin7,  { cell n; return Utils::ReadBinary(S"0b1001)", n) == OK && n == 9; })
TEST(Bin7b, { cell n; return Utils::ReadBinary(S"0b0110)", n) == OK && n == 6; })
TEST(Bin8,  { cell n; return Utils::ReadBinary(S"0B1111G", n) == OK && n == 15; })
// Test invalid formats.
TEST(Bin9,  { cell n; return Utils::ReadBinary(S"2", n) == ERROR_NAN; })
TEST(Bin10, { cell n; return Utils::ReadBinary(S"(1)", n) == ERROR_NAN; })
TEST(Bin11, { cell n; return Utils::ReadBinary(S"-0", n) == ERROR_NAN; })
TEST(Bin12, { cell n; return Utils::ReadBinary(S"", n) == ERROR_NAN; })

error_t
	Utils::
	ReadChar(char const * & input, cell & n)
{
	switch ((n = *input))
	{
		case '\0': return ERROR_NAN;
		case '\\':
			++input;
			switch (*input)
			{
				case 'n':  n = '\n'; break;
				case '\\': n = '\\'; break;
				case '\'': n = '\''; break;
				case 't':  n = '\t'; break;
				case '"':  n = '\"'; break;
				case 'a':  n = '\a'; break;
				case 'b':  n = '\b'; break;
				case 'v':  n = '\v'; break;
				case 'r':  n = '\r'; break;
				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
				{
					// Can't fail, already validated.
					Utils::ReadOctal(input, n);
					if (*input == ';') ++input;
					return OK;
				}
				case 'x': case 'X':
				{
					++input;
					TRY(Utils::ReadHex(input, n));
					if (*input == ';') ++input;
					return OK;
				}
				default: return ERROR_INVALID_ESCAPE;
			}
			break;
	}
	++input;
	return OK;
}

error_t
	Utils::
	ReadCharEx(char const * & input, cell & n)
{
	// Detect enclosing quotes.
	bool
		quotes = false;
	if (*input == '\'')
	{
		quotes = true;
		++input;
	}
	TRY(Utils::ReadChar(input, n));
	if (quotes)
	{
		FAIL(*input == '\'', ERROR_UNCLOSED_CHARACTER_LIT);
		++input;
	}
	return OK;
}

TEST(Char0,  { cell n; return Utils::ReadChar(S"0", n) == OK && n == '0'; })
TEST(Char1,  { cell n; return Utils::ReadChar(S"x", n) == OK && n == 'x'; })
TEST(Char2a, { cell n; return Utils::ReadChar(S"\\\\", n) == OK && n == '\\'; })
TEST(Char2b, { cell n; return Utils::ReadChar(S"\\n", n) == OK && n == '\n'; })
TEST(Char2c, { cell n; return Utils::ReadChar(S"\\0", n) == OK && n == 0; })
TEST(Char2d, { cell n; return Utils::ReadChar(S"\\55", n) == OK && n == 055; })
TEST(Char2e, { cell n; return Utils::ReadChar(S"\\55;", n) == OK && n == 055; })
TEST(Char2f, { cell n; return Utils::ReadChar(S"\\'", n) == OK && n == '\''; })
TEST(Char2g, { cell n; return Utils::ReadChar(S"\\", n) == ERROR_INVALID_ESCAPE; })
TEST(Char2h, { cell n; return Utils::ReadChar(S"\\y", n) == ERROR_INVALID_ESCAPE; })
TEST(Char2i, { cell n; return Utils::ReadChar(S"\\9", n) == ERROR_INVALID_ESCAPE; })
TEST(Char2j, { cell n; return Utils::ReadChar(S"\\x;", n) == ERROR_NAN; })
TEST(Char2k, { cell n; return Utils::ReadChar(S"\\xH;", n) == ERROR_NAN; })
TEST(Char3,  { cell n; return Utils::ReadChar(S"'g'", n) == OK && n == '\''; })
TEST(Char4a, { cell n; return Utils::ReadCharEx(S"'g'", n) == OK && n == 'g'; })
TEST(Char4b, { cell n; return Utils::ReadCharEx(S"g", n) == OK && n == 'g'; })
TEST(Char4c, { cell n; return Utils::ReadCharEx(S"", n) == ERROR_NAN; })
TEST(Char4d, { cell n; return Utils::ReadCharEx(S"\\'", n) == OK && n == '\''; })
TEST(Char4e, { cell n; return Utils::ReadCharEx(S"'\\''", n) == OK && n == '\''; })
TEST(Char4f, { cell n; return Utils::ReadCharEx(S"\\'j'", n) == OK && n == '\''; })

/*
error_t
	Utils::
	GetArraySize(char const * & input, int * size, bool empty)
{
	NEXT(input, '[', ERROR_NO_ARRAY_START);
	// Capital letter - read in the deafult.
	*size = -1;
	// Skip the opening bracket.
	if (*input == '*')
	{
		++input;
	}
	else
	{
		cell
			dest;
		error_t
			error = ReadDecimal(input, dest);
		*size = dest;
		if (error == ERROR_NAN)
		{
			if (!empty) return ERROR_NAN;
			if (!*input) return ERROR_NO_ARRAY_END;
			NEXT(input, ']', ERROR_NAN);
			return OK;
		}
		else
		{
			TRY(error);
			if (*size < 1) return ERROR_INVALID_ARRAY_SIZE;
		}
	}
	NEXT(input, ']', ERROR_NO_ARRAY_END);
	return OK;
}

// No size given.
TEST(Arr0a, { int size; return Utils::GetArraySize(S"[]", &size) == ERROR_NAN; })
TEST(Arr0b, { int size; return Utils::GetArraySize(S"[]", &size, false) == ERROR_NAN; })
TEST(Arr0c, { int size; return Utils::GetArraySize(S"[]", &size, true) == OK && size == 0; })
TEST(Arr0d, { int size; return Utils::GetArraySize(S"[ ]", &size) == ERROR_NAN; })
TEST(Arr0e, { int size; return Utils::GetArraySize(S"[ ]", &size, false) == ERROR_NAN; })
TEST(Arr0f, { int size; return Utils::GetArraySize(S"[ ]", &size, true) == OK && size == 0; })
TEST(Arr0g, { int size; return Utils::GetArraySize(S"[  ]", &size) == ERROR_NAN; })
TEST(Arr0h, { int size; return Utils::GetArraySize(S"[  ]", &size, false) == ERROR_NAN; })
TEST(Arr0i, { int size; return Utils::GetArraySize(S"[  ]", &size, true) == OK && size == 0; })
// Failures.
TEST(Arr1a, { int size; return Utils::GetArraySize(S"[5", &size) == ERROR_NO_ARRAY_END; })
TEST(Arr1b, { int size; return Utils::GetArraySize(S"[", &size) == ERROR_NAN; })
TEST(Arr1h, { int size; return Utils::GetArraySize(S"[", &size, true) == ERROR_NO_ARRAY_END; })
TEST(Arr1c, { int size; return Utils::GetArraySize(S"[g]", &size) == ERROR_NAN; })
TEST(Arr1d, { int size; return Utils::GetArraySize(S"[g]", &size, true) == ERROR_NAN; }) // FAILED.
TEST(Arr1e, { int size; return Utils::GetArraySize(S"", &size, true) == ERROR_NO_ARRAY_START; })
TEST(Arr1f, { int size; return Utils::GetArraySize(S"5", &size, true) == ERROR_NO_ARRAY_START; })
TEST(Arr1g, { int size; return Utils::GetArraySize(S"]", &size, true) == ERROR_NO_ARRAY_START; })
// OK.
TEST(Arr2,  { int size; return Utils::GetArraySize(S"[42]", &size) == OK && size == 42; })
TEST(Arr2a, { int size; return Utils::GetArraySize(S" [43]", &size) == OK && size == 43; })
TEST(Arr2b, { int size; return Utils::GetArraySize(S"  [44]", &size) == OK && size == 44; })
TEST(Arr2c, { int size; return Utils::GetArraySize(S"   [45]", &size) == OK && size == 45; })
TEST(Arr3,  { int size; return Utils::GetArraySize(S"[ 11 ]", &size) == OK && size == 11; })
TEST(Arr4,  { int size; return Utils::GetArraySize(S"[6 ]", &size) == OK && size == 6; })
TEST(Arr5,  { int size; return Utils::GetArraySize(S"[ 7]", &size) == OK && size == 7; })
TEST(Arr6,  { int size; return Utils::GetArraySize(S"[  8888  ]", &size) == OK && size == 8888; })
// More fails.
TEST(Arr7,  { int size; return Utils::GetArraySize(S"[3 9]", &size) == ERROR_NO_ARRAY_END; })
TEST(Arr8a, { int size; return Utils::GetArraySize(S"[0]", &size) == ERROR_INVALID_ARRAY_SIZE; })
TEST(Arr9a, { int size; return Utils::GetArraySize(S"[-05]", &size) == ERROR_INVALID_ARRAY_SIZE; })
TEST(Arr8b, { int size; return Utils::GetArraySize(S"[-90]", &size, true) == ERROR_INVALID_ARRAY_SIZE; })
TEST(Arr9b, { int size; return Utils::GetArraySize(S"[-111]", &size, true) == ERROR_INVALID_ARRAY_SIZE; })
// Variable.
TEST(Arr10a, { int size; return Utils::GetArraySize(S"[*]", &size) == OK && size == -1; })
TEST(Arr10b, { int size; return Utils::GetArraySize(S"[ *]", &size, true) == OK && size == -1; })
TEST(Arr10c, { int size; return Utils::GetArraySize(S"[* ]", &size) == OK && size == -1; })
TEST(Arr10d, { int size; return Utils::GetArraySize(S"[ * ]", &size, true) == OK && size == -1; })
TEST(Arr10e, { int size; return Utils::GetArraySize(S" [*]", &size) == OK && size == -1; })
TEST(Arr10f, { int size; return Utils::GetArraySize(S" [ * ]", &size, true) == OK && size == -1; })
*/

void
	Utils::
	SkipWhitespace(char const * & input)
{
	while ('\0' < (unsigned char)*input && (unsigned char)*input <= ' ') ++input;
}

/*
bool
	IsIn(char c, char * ls)
{
	while (*ls) if (c == *ls++) return true;
	return false;
}

error_t
	Utils::
	GetStringLength(char const * start, char * delims, size_t * len)
{
	Utils::SkipWhitespace(start);
	cell
		ch;
	size_t
		tlen = 0,
		possibleLen = 0;
	while (*start)
	{
		if (IsIn(*start, delims)) break;
		else if ((unsigned char)*start > ' ')
		{
			TRY(ReadChar(start, ch));
			possibleLen = ++tlen;
		}
		else
		{
			++start;
			++tlen;
		}
	}
	FAIL(*start, ERROR_NO_STRING_END);
	// Skip trailing spaces.
	*len = possibleLen;
	return OK;
}

TEST(GetStringLen1,  { size_t len; return Utils::GetStringLength("'", "'", &len) == OK && len == 0; })
TEST(GetStringLen2,  { size_t len; return Utils::GetStringLength("aa'", "'", &len) == OK && len == 2; })
TEST(GetStringLen3,  { size_t len; return Utils::GetStringLength("aaabb2 '", "'", &len) == OK && len == 6; })
TEST(GetStringLen4,  { size_t len; return Utils::GetStringLength("aaabb2 #'", "'", &len) == OK && len == 8; })
TEST(GetStringLen5,  { size_t len; return Utils::GetStringLength("  342t'", "'", &len) == OK && len == 4; })
TEST(GetStringLen6,  { size_t len; return Utils::GetStringLength(" etl4  #  '", "'", &len) == OK && len == 7; })
TEST(GetStringLen7,  { size_t len; return Utils::GetStringLength(" et\\'4  #  '", "'", &len) == OK && len == 7; })
TEST(GetStringLen8,  { size_t len; return Utils::GetStringLength("\\\\'", "'", &len) == OK && len == 1; })
TEST(GetStringLen9,  { size_t len; return Utils::GetStringLength("\\\"'", "'", &len) == OK && len == 1; })
TEST(GetStringLen10, { size_t len; return Utils::GetStringLength("\"  g '", "'", &len) == OK && len == 4; })
TEST(GetStringLen11, { size_t len; return Utils::GetStringLength("asd", "'", &len) == ERROR_NO_STRING_END; })
TEST(GetStringLen12, { size_t len; return Utils::GetStringLength("\\x56;'", "'", &len) == OK && len == 1; })
TEST(GetStringLen13, { size_t len; return Utils::GetStringLength("\\123'", "'", &len) == OK && len == 1; })
// Valid octal number.
TEST(GetStringLen14, { size_t len; return Utils::GetStringLength("\\476;'", "'", &len) == OK && len == 1; })
// Not a valid octal number, just return the rest as characters.
TEST(GetStringLen15, { size_t len; return Utils::GetStringLength("\\478;'", "'", &len) == OK && len == 3; })

error_t
	Utils::
	GetString(cell * dest, char const * & input, size_t len)
{
	Utils::SkipWhitespace(input);
	size_t
		read = 0;
	while (*input && read < len)
	{
		TRY(Utils::ReadChar(input, *dest));
		++read;
		++dest;
	}
	*dest = '\0';
	return OK;
}

TEST(GetString1a, { cell dest[28]; return Utils::GetString(dest, S"  a\\\\\\\' \\x1235D;'", 5) == OK; })
TEST(GetString1e, { cell dest[28]; Utils::GetString(dest, S"  a\\\\\\\' \\x1235D;'", 5); return true; })
TEST(GetString1b, { cell dest[28]; return Utils::GetString(dest, S"  a\\\\\\\' \\x1235D;'", 5) == OK && *CUR == '\''; })
TEST(GetString1c, { cell dest[28]; return Utils::GetString(dest, S"  a\\\\\\\' \\x1235D;'", 5) == OK &&
	dest[0] == 'a' &&
	dest[1] == '\\' &&
	dest[2] == '\''; })
TEST(GetString1d, { cell dest[28]; return Utils::GetString(dest, S"  a\\\\\\\' \\x1235D;'", 5) == OK &&
	dest[3] == ' ' &&
	dest[4] == 0x1235D; })
*/

error_t
	Utils::
	GetBounded(char const * & input, char const * & output, char start, char end, size_t * len)
{
	NEXT(input, start, ERROR_EXPECTED_A_GOT_B_1);
	output = input;
	char const *
		ep = input;
	cell
		ch;
	while (*input)
	{
		if (*input == end) break;
		else if ((unsigned char)*input > ' ')
		{
			TRY(Utils::ReadChar(input, ch));
			ep = input;
		}
		else
		{
			++input;
		}
	}
	if (*input != end) return ERROR_EXPECTED_A_GOT_B_2;
	*const_cast<char *>(ep) = '\0';
	if (len) *len = ep - output;
	++input;
	Utils::SkipWhitespace(input);
	return OK;
}

TEST(GetBound0,  { char const * c; return Utils::GetBounded(S"   hello\"", c, '"', '"') == ERROR_EXPECTED_A_GOT_B_1; })
TEST(GetBound1,  { char const * c; return Utils::GetBounded(S"   \"hello", c, '"', '"') == ERROR_EXPECTED_A_GOT_B_2; })
TEST(GetBound2,  { char const * c; return Utils::GetBounded(S"   \"hello  \"", c, '"', '"') == OK; })
TEST(GetBound3,  { char const * c; return Utils::GetBounded(S"   \"hello  \"", c, '"', '"') == OK && std::string(c) == "hello"; })
TEST(GetBound4,  { char const * c; return Utils::GetBounded(S"   \"   hello  \"", c, '"', '"') == OK && std::string(c) == "hello"; })
TEST(GetBound5,  { char const * c; return Utils::GetBounded(S"   \"hello\"", c, '"', '"') == OK && std::string(c) == "hello"; })
TEST(GetBound6,  { char const * c; return Utils::GetBounded(S"   (hello	)", c, '(', ')') == OK && std::string(c) == "hello"; })
TEST(GetBound7,  { char const * c; return Utils::GetBounded(S"   <	hello	>", c, '<', '>') == OK && std::string(c) == "hello"; })
TEST(GetBound8,  { char const * c; return Utils::GetBounded(S"   [hello]", c, '[', ']') == OK && std::string(c) == "hello"; })
TEST(GetBound9,  { char const * c; size_t len; return Utils::GetBounded(S"   [hello ]", c, '[', ']', &len) == OK && len == 5; })
TEST(GetBound10, { char const * c; size_t len; return Utils::GetBounded(S"   [ hello g]", c, '[', ']', &len) == OK && len == 7; })
TEST(GetBound11, { char const * c; size_t len; return Utils::GetBounded(S"   !h ello   543#", c, '!', '#', &len) == OK && len == 12; })

error_t
	Utils::
	GetDefaults(char const * & input, char const * & output, size_t * len)
{
	error_t
		error = Utils::GetBounded(input, output, '(', ')', len);
	switch (error)
	{
		case OK: return OK;
		case ERROR_EXPECTED_A_GOT_B_1: FAIL(false, ERROR_NO_DEFAULT_START);
		case ERROR_EXPECTED_A_GOT_B_2: FAIL(false, ERROR_NO_DEFAULT_END);
	}
	return error;
};

error_t
	Utils::
	GetParams(char const * & input, char const * & output, size_t * len)
{
	error_t
		error = Utils::GetBounded(input, output, '<', '>', len);
	switch (error)
	{
		case OK: return OK;
		case ERROR_EXPECTED_A_GOT_B_1: FAIL(false, ERROR_NO_PARAM_START);
		case ERROR_EXPECTED_A_GOT_B_2: FAIL(false, ERROR_NO_PARAM_END);
	}
	return error;
};

error_t
	Utils::
	GetSizes(char const * & input, char const * & output, size_t * len)
{
	error_t
		error = Utils::GetBounded(input, output, '[', ']', len);
	switch (error)
	{
		case OK: return OK;
		case ERROR_EXPECTED_A_GOT_B_1: FAIL(false, ERROR_NO_ARRAY_START);
		case ERROR_EXPECTED_A_GOT_B_2: FAIL(false, ERROR_NO_ARRAY_END);
	}
	return error;
};

error_t
	Utils::
	GetString(char const * & input, char const * & output, char const t, size_t * len)
{
	error_t
		error = Utils::GetBounded(input, output, t, t, len);
	switch (error)
	{
		case OK: return OK;
		case ERROR_EXPECTED_A_GOT_B_1: FAIL(false, ERROR_EXPECTED_A_GOT_B_2, t, *input);
		case ERROR_EXPECTED_A_GOT_B_2: FAIL(false, ERROR_NO_STRING_END);
	}
	return error;
};

error_t
	Utils::
	CopyString(cell * dest, char const * src, size_t len, bool pad)
{
	FAIL(len, ERROR_MEMORY_ALLOCATION_FAIL);
	while (--len && *src)
	{
		TRY(Utils::ReadChar(src, *dest));
		++dest;
	}
	// Always has one character reserved for "NULL".
	*dest++ = '\0';
	if (pad)
	{
		while (len--) *dest++ = '\0';
	}
	return OK;
};

#ifdef SSCANF_DEBUG

bool TestCompare(char const * one, cell const * two)
{
	while (*two) if (*one++ != *two++) return false;
	return *one == '\0';
}

#endif

TEST(CopyStr0,  { cell dest[42]; return Utils::CopyString(dest, S"Hello", 5, false) == OK && TestCompare("Hell", dest); })
TEST(CopyStr1,  { cell dest[7]; dest[6] = 42; return Utils::CopyString(dest, S"Hello", 7, false) == OK && TestCompare("Hello", dest) && dest[6] == 42; })
TEST(CopyStr2,  { cell dest[7]; dest[6] = 42; return Utils::CopyString(dest, S"world", 7, true) == OK && TestCompare("world", dest) && dest[6] == 0; })


