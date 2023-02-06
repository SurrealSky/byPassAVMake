#pragma once
#include<Windows.h>
#include<string>
using namespace std;
#include<typedef.h>
using namespace SurrealTypes;

namespace SurrealConvert
{
	/* Some fundamental constants */
	#define UNI_REPLACEMENT_CHAR (STu32)0x0000FFFD
	#define UNI_MAX_BMP (STu32)0x0000FFFF
	#define UNI_MAX_STu16 (STu32)0x0010FFFF
	#define UNI_MAX_STu32 (STu32)0x7FFFFFFF
	#define UNI_MAX_LEGAL_STu32 (STu32)0x0010FFFF

	typedef enum {
		conversionOK, 		/* conversion successful */
		sourceExhausted,	/* partial character in source, but hit end */
		targetExhausted,	/* insuff. room in target for conversion */
		sourceIllegal		/* source sequence is illegal/malformed */
	} ConversionResult;

	typedef enum {
		strictConversion = 0,
		lenientConversion
	} ConversionFlags;

	static const int halfShift = 10; /* used for shifting by 10 bits */

	static const STu32 halfBase = 0x0010000UL;
	static const STu32 halfMask = 0x3FFUL;

	#define UNI_SUR_HIGH_START  (STu32)0xD800
	#define UNI_SUR_HIGH_END    (STu32)0xDBFF
	#define UNI_SUR_LOW_START   (STu32)0xDC00
	#define UNI_SUR_LOW_END     (STu32)0xDFFF
	#define false	   0
	#define true	    1

	static const char trailingBytesForSTu8[256] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
	};

	static const STu32 offsetsFromSTu8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
		0x03C82080UL, 0xFA082080UL, 0x82082080UL };

	static const STu8 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

	class CodedConvert
	{
	public:
		CodedConvert()
		{
		}
		~CodedConvert()
		{

		}
	public:
		wstring AsciiToUnicode(const string& str) {
			// 预算-缓冲区中宽字节的长度    
			int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
			// 给指向缓冲区的指针变量分配内存    
			wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
			// 开始向缓冲区转换字节    
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
			wstring ret_str = pUnicode;
			free(pUnicode);
			return ret_str;
		}
		string UnicodeToAscii(const wstring& wstr) {
			// 预算-缓冲区中多字节的长度    
			int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
			// 给指向缓冲区的指针变量分配内存    
			char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
			// 开始向缓冲区转换字节    
			WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
			string ret_str = pAssii;
			free(pAssii);
			return ret_str;
		}
		wstring STu8ToUnicode(const string& str) {
			// 预算-缓冲区中宽字节的长度    
			int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
			// 给指向缓冲区的指针变量分配内存    
			wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
			// 开始向缓冲区转换字节    
			MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);
			wstring ret_str = pUnicode;
			free(pUnicode);
			return ret_str;
		}
		string UnicodeToSTu8(const wstring& wstr) {
			// 预算-缓冲区中多字节的长度    
			int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
			// 给指向缓冲区的指针变量分配内存    
			char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
			// 开始向缓冲区转换字节    
			WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
			string ret_str = pAssii;
			free(pAssii);
			return ret_str;
		}
		string AsciiToSTu8(const string& str) {
			return UnicodeToSTu8(AsciiToUnicode(str));
		}
		string STu8ToAscii(const string& str) {
			return UnicodeToAscii(STu8ToUnicode(str));
		}

	private:
		STbool isLegalSTu8(const STu8 *source, int length) {
			STu8 a;
			const STu8 *srcptr = source + length;
			switch (length) {
			default: return false;
				/* Everything else falls through when "true"... */
			case 4: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
			case 3: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
			case 2: if ((a = (*--srcptr)) > 0xBF) return false;

				switch (*source) {
					/* no fall-through in this inner switch */
				case 0xE0: if (a < 0xA0) return false; break;
				case 0xED: if (a > 0x9F) return false; break;
				case 0xF0: if (a < 0x90) return false; break;
				case 0xF4: if (a > 0x8F) return false; break;
				default:   if (a < 0x80) return false;
				}

			case 1: if (*source >= 0x80 && *source < 0xC2) return false;
			}
			if (*source > 0xF4) return false;
			return true;
		}

	public:
		ConversionResult ConvertSTu32toSTu16(
			const STu32** sourceStart, const STu32* sourceEnd,
			STu16** targetStart, STu16* targetEnd, ConversionFlags flags) {
			ConversionResult result = conversionOK;
			const STu32* source = *sourceStart;
			STu16* target = *targetStart;
			while (source < sourceEnd) {
				STu32 ch;
				if (target >= targetEnd) {
					result = targetExhausted; break;
				}
				ch = *source++;
				if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
										 /* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
					if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
						if (flags == strictConversion) {
							--source; /* return to the illegal value itself */
							result = sourceIllegal;
							break;
						}
						else {
							*target++ = UNI_REPLACEMENT_CHAR;
						}
					}
					else {
						*target++ = (STu16)ch; /* normal case */
					}
				}
				else if (ch > UNI_MAX_LEGAL_STu32) {
					if (flags == strictConversion) {
						result = sourceIllegal;
					}
					else {
						*target++ = UNI_REPLACEMENT_CHAR;
					}
				}
				else {
					/* target is a character in range 0xFFFF - 0x10FFFF. */
					if (target + 1 >= targetEnd) {
						--source; /* Back up source pointer! */
						result = targetExhausted; break;
					}
					ch -= halfBase;
					*target++ = (STu16)((ch >> halfShift) + UNI_SUR_HIGH_START);
					*target++ = (STu16)((ch & halfMask) + UNI_SUR_LOW_START);
				}
			}
			*sourceStart = source;
			*targetStart = target;
			return result;
		}

		ConversionResult ConvertSTu16toSTu32(
			const STu16** sourceStart, const STu16* sourceEnd,
			STu32** targetStart, STu32* targetEnd, ConversionFlags flags) {
			ConversionResult result = conversionOK;
			const STu16* source = *sourceStart;
			STu32* target = *targetStart;
			STu32 ch, ch2;
			while (source < sourceEnd) {
				const STu16* oldSource = source; /*  In case we have to back up because of target overflow. */
				ch = *source++;
				/* If we have a surrogate pair, convert to STu32 first. */
				if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END) {
					/* If the 16 bits following the high surrogate are in the source buffer... */
					if (source < sourceEnd) {
						ch2 = *source;
						/* If it's a low surrogate, convert to STu32. */
						if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END) {
							ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
								+ (ch2 - UNI_SUR_LOW_START) + halfBase;
							++source;
						}
						else if (flags == strictConversion) { /* it's an unpaired high surrogate */
							--source; /* return to the illegal value itself */
							result = sourceIllegal;
							break;
						}
					}
					else { /* We don't have the 16 bits following the high surrogate. */
						--source; /* return to the high surrogate */
						result = sourceExhausted;
						break;
					}
				}
				else if (flags == strictConversion) {
					/* UTF-16 surrogate values are illegal in UTF-32 */
					if (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END) {
						--source; /* return to the illegal value itself */
						result = sourceIllegal;
						break;
					}
				}
				if (target >= targetEnd) {
					source = oldSource; /* Back up source pointer! */
					result = targetExhausted; break;
				}
				*target++ = ch;
			}
			*sourceStart = source;
			*targetStart = target;
#ifdef CVTUTF_DEBUG
			if (result == sourceIllegal) {
				fprintf(stderr, "ConvertSTu16toSTu32 illegal seq 0x%04x,%04x\n", ch, ch2);
				fflush(stderr);
			}
#endif
			return result;
		}

		ConversionResult ConvertSTu16toSTu8(
			const STu16** sourceStart, const STu16* sourceEnd,
			STu8** targetStart, STu8* targetEnd, ConversionFlags flags) {
			ConversionResult result = conversionOK;
			const STu16* source = *sourceStart;
			STu8* target = *targetStart;
			while (source < sourceEnd) {
				STu32 ch;
				unsigned short bytesToWrite = 0;
				const STu32 byteMask = 0xBF;
				const STu32 byteMark = 0x80;
				const STu16* oldSource = source; /* In case we have to back up because of target overflow. */
				ch = *source++;
				/* If we have a surrogate pair, convert to STu32 first. */
				if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END) {
					/* If the 16 bits following the high surrogate are in the source buffer... */
					if (source < sourceEnd) {
						STu32 ch2 = *source;
						/* If it's a low surrogate, convert to STu32. */
						if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END) {
							ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
								+ (ch2 - UNI_SUR_LOW_START) + halfBase;
							++source;
						}
						else if (flags == strictConversion) { /* it's an unpaired high surrogate */
							--source; /* return to the illegal value itself */
							result = sourceIllegal;
							break;
						}
					}
					else { /* We don't have the 16 bits following the high surrogate. */
						--source; /* return to the high surrogate */
						result = sourceExhausted;
						break;
					}
				}
				else if (flags == strictConversion) {
					/* UTF-16 surrogate values are illegal in UTF-32 */
					if (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END) {
						--source; /* return to the illegal value itself */
						result = sourceIllegal;
						break;
					}
				}
				/* Figure out how many bytes the result will require */
				if (ch < (STu32)0x80) {
					bytesToWrite = 1;
				}
				else if (ch < (STu32)0x800) {
					bytesToWrite = 2;
				}
				else if (ch < (STu32)0x10000) {
					bytesToWrite = 3;
				}
				else if (ch < (STu32)0x110000) {
					bytesToWrite = 4;
				}
				else {
					bytesToWrite = 3;
					ch = UNI_REPLACEMENT_CHAR;
				}

				target += bytesToWrite;
				if (target > targetEnd) {
					source = oldSource; /* Back up source pointer! */
					target -= bytesToWrite; result = targetExhausted; break;
				}
				switch (bytesToWrite) { /* note: everything falls through. */
				case 4: *--target = (STu8)((ch | byteMark) & byteMask); ch >>= 6;
				case 3: *--target = (STu8)((ch | byteMark) & byteMask); ch >>= 6;
				case 2: *--target = (STu8)((ch | byteMark) & byteMask); ch >>= 6;
				case 1: *--target = (STu8)(ch | firstByteMark[bytesToWrite]);
				}
				target += bytesToWrite;
			}
			*sourceStart = source;
			*targetStart = target;
			return result;
		}

		STbool isLegalSTu8Sequence(const STu8 *source, const STu8 *sourceEnd) {
			int length = trailingBytesForSTu8[*source] + 1;
			if (source + length > sourceEnd) {
				return false;
			}
			return isLegalSTu8(source, length);
		}

		ConversionResult ConvertSTu8toSTu16(
			const STu8** sourceStart, const STu8* sourceEnd,
			STu16** targetStart, STu16* targetEnd, ConversionFlags flags) {
			ConversionResult result = conversionOK;
			const STu8* source = *sourceStart;
			STu16* target = *targetStart;
			while (source < sourceEnd) {
				STu32 ch = 0;
				unsigned short extraBytesToRead = trailingBytesForSTu8[*source];
				if (source + extraBytesToRead >= sourceEnd) {
					result = sourceExhausted; break;
				}
				/* Do this check whether lenient or strict */
				if (!isLegalSTu8(source, extraBytesToRead + 1)) {
					result = sourceIllegal;
					break;
				}
				/*
				* The cases all fall through. See "Note A" below.
				*/
				switch (extraBytesToRead) {
				case 5: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
				case 4: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
				case 3: ch += *source++; ch <<= 6;
				case 2: ch += *source++; ch <<= 6;
				case 1: ch += *source++; ch <<= 6;
				case 0: ch += *source++;
				}
				ch -= offsetsFromSTu8[extraBytesToRead];

				if (target >= targetEnd) {
					source -= (extraBytesToRead + 1); /* Back up source pointer! */
					result = targetExhausted; break;
				}
				if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
										 /* UTF-16 surrogate values are illegal in UTF-32 */
					if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
						if (flags == strictConversion) {
							source -= (extraBytesToRead + 1); /* return to the illegal value itself */
							result = sourceIllegal;
							break;
						}
						else {
							*target++ = UNI_REPLACEMENT_CHAR;
						}
					}
					else {
						*target++ = (STu16)ch; /* normal case */
					}
				}
				else if (ch > UNI_MAX_STu16) {
					if (flags == strictConversion) {
						result = sourceIllegal;
						source -= (extraBytesToRead + 1); /* return to the start */
						break; /* Bail out; shouldn't continue */
					}
					else {
						*target++ = UNI_REPLACEMENT_CHAR;
					}
				}
				else {
					/* target is a character in range 0xFFFF - 0x10FFFF. */
					if (target + 1 >= targetEnd) {
						source -= (extraBytesToRead + 1); /* Back up source pointer! */
						result = targetExhausted; break;
					}
					ch -= halfBase;
					*target++ = (STu16)((ch >> halfShift) + UNI_SUR_HIGH_START);
					*target++ = (STu16)((ch & halfMask) + UNI_SUR_LOW_START);
				}
			}
			*sourceStart = source;
			*targetStart = target;
			return result;
		}

		ConversionResult ConvertSTu32toSTu8(
			const STu32** sourceStart, const STu32* sourceEnd,
			STu8** targetStart, STu8* targetEnd, ConversionFlags flags) {
			ConversionResult result = conversionOK;
			const STu32* source = *sourceStart;
			STu8* target = *targetStart;
			while (source < sourceEnd) {
				STu32 ch;
				unsigned short bytesToWrite = 0;
				const STu32 byteMask = 0xBF;
				const STu32 byteMark = 0x80;
				ch = *source++;
				if (flags == strictConversion) {
					/* UTF-16 surrogate values are illegal in UTF-32 */
					if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
						--source; /* return to the illegal value itself */
						result = sourceIllegal;
						break;
					}
				}
				/*
				* Figure out how many bytes the result will require. Turn any
				* illegally large STu32 things (> Plane 17) into replacement chars.
				*/
				if (ch < (STu32)0x80) {
					bytesToWrite = 1;
				}
				else if (ch < (STu32)0x800) {
					bytesToWrite = 2;
				}
				else if (ch < (STu32)0x10000) {
					bytesToWrite = 3;
				}
				else if (ch <= UNI_MAX_LEGAL_STu32) {
					bytesToWrite = 4;
				}
				else {
					bytesToWrite = 3;
					ch = UNI_REPLACEMENT_CHAR;
					result = sourceIllegal;
				}

				target += bytesToWrite;
				if (target > targetEnd) {
					--source; /* Back up source pointer! */
					target -= bytesToWrite; result = targetExhausted; break;
				}
				switch (bytesToWrite) { /* note: everything falls through. */
				case 4: *--target = (STu8)((ch | byteMark) & byteMask); ch >>= 6;
				case 3: *--target = (STu8)((ch | byteMark) & byteMask); ch >>= 6;
				case 2: *--target = (STu8)((ch | byteMark) & byteMask); ch >>= 6;
				case 1: *--target = (STu8)(ch | firstByteMark[bytesToWrite]);
				}
				target += bytesToWrite;
			}
			*sourceStart = source;
			*targetStart = target;
			return result;
		}

		ConversionResult ConvertSTu8toSTu32(
			const STu8** sourceStart, const STu8* sourceEnd,
			STu32** targetStart, STu32* targetEnd, ConversionFlags flags) {
			ConversionResult result = conversionOK;
			const STu8* source = *sourceStart;
			STu32* target = *targetStart;
			while (source < sourceEnd) {
				STu32 ch = 0;
				unsigned short extraBytesToRead = trailingBytesForSTu8[*source];
				if (source + extraBytesToRead >= sourceEnd) {
					result = sourceExhausted; break;
				}
				/* Do this check whether lenient or strict */
				if (!isLegalSTu8(source, extraBytesToRead + 1)) {
					result = sourceIllegal;
					break;
				}
				/*
				* The cases all fall through. See "Note A" below.
				*/
				switch (extraBytesToRead) {
				case 5: ch += *source++; ch <<= 6;
				case 4: ch += *source++; ch <<= 6;
				case 3: ch += *source++; ch <<= 6;
				case 2: ch += *source++; ch <<= 6;
				case 1: ch += *source++; ch <<= 6;
				case 0: ch += *source++;
				}
				ch -= offsetsFromSTu8[extraBytesToRead];

				if (target >= targetEnd) {
					source -= (extraBytesToRead + 1); /* Back up the source pointer! */
					result = targetExhausted; break;
				}
				if (ch <= UNI_MAX_LEGAL_STu32) {
					/*
					* UTF-16 surrogate values are illegal in UTF-32, and anything
					* over Plane 17 (> 0x10FFFF) is illegal.
					*/
					if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
						if (flags == strictConversion) {
							source -= (extraBytesToRead + 1); /* return to the illegal value itself */
							result = sourceIllegal;
							break;
						}
						else {
							*target++ = UNI_REPLACEMENT_CHAR;
						}
					}
					else {
						*target++ = ch;
					}
				}
				else { /* i.e., ch > UNI_MAX_LEGAL_STu32 */
					result = sourceIllegal;
					*target++ = UNI_REPLACEMENT_CHAR;
				}
			}
			*sourceStart = source;
			*targetStart = target;
			return result;
		}
	};
}



