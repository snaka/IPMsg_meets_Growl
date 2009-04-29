#include <stdio.h>
#include <windows.h>

BOOL convSJIStoUTF8( BYTE* pSource, BYTE* pDist, int* pSize ) 
{
	*pSize = 0;

	// Convert SJIS -> UTF-16
	const int nSize = ::MultiByteToWideChar( CP_ACP, 0, (LPCSTR)pSource, -1, NULL, 0 );

	BYTE* buffUtf16 = new BYTE[ nSize * 2 + 2 ];
	::MultiByteToWideChar( CP_ACP, 0, (LPCSTR)pSource, -1, (LPWSTR)buffUtf16, nSize );

	// Convert UTF-16 -> UTF-8
	const int nSizeUtf8 = ::WideCharToMultiByte( CP_UTF8, 0, (LPCWSTR)buffUtf16, -1, NULL, 0, NULL, NULL );
	if ( !pDist ) {
		*pSize = nSizeUtf8;
		delete buffUtf16;
		return TRUE;
	}

	BYTE* buffUtf8 = new BYTE[ nSizeUtf8 * 2 ];
	ZeroMemory( buffUtf8, nSizeUtf8 * 2 );
	::WideCharToMultiByte( CP_UTF8, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)buffUtf8, nSizeUtf8, NULL, NULL );

	*pSize = lstrlen( (char*)buffUtf8 );
	memcpy( pDist, buffUtf8, *pSize );

	delete buffUtf16;
	delete buffUtf8;

	return TRUE;
}

/*
 * convert: sjis -> utf8
 */
BYTE* sjis2utf8(BYTE* source) {
	// Calculate result size
	int size = 0;
	convSJIStoUTF8( source, NULL, &size );

	// Peform convert
	BYTE* dest = new BYTE[ size + 1 ];
	ZeroMemory( dest, size + 1 );
	convSJIStoUTF8( source, dest, &size );

	return dest;
}

/*
 * main
 */
/*
int main(int argc, char* argv[]) 
{
	if (argc != 2) {
		printf("Usage: sjis2u string...\n");
		exit(-1);
	}

	BYTE* dest;
	sjis2utf8((BYTE*)argv[1], &dest);

	// Convert result (UTF-8)
	printf((char*)dest);
}
*/
