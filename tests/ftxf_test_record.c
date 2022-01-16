/*
 * Library record type test program
 *
 * Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "ftxf_test_libcerror.h"
#include "ftxf_test_libftxf.h"
#include "ftxf_test_macros.h"
#include "ftxf_test_memory.h"
#include "ftxf_test_unused.h"

#include "../libftxf/libftxf_record.h"

uint8_t ftxf_test_record_data1[ 208 ] = {
	0x01, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x20, 0x38, 0x49, 0x00, 0x00, 0x00, 0x00,
	0xfc, 0xc3, 0xf0, 0x82, 0xfb, 0x88, 0xe3, 0x11, 0x8b, 0x6e, 0x52, 0x54, 0x00, 0x12, 0x34, 0x56,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xbc, 0x43, 0xc6, 0x10, 0x1d, 0xcf, 0x01,
	0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00,
	0x49, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
	0x16, 0x42, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x93, 0x06, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x06, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00,
	0x28, 0x00, 0x3c, 0x00, 0x46, 0x00, 0x6f, 0x00, 0x6e, 0x00, 0x74, 0x00, 0x43, 0x00, 0x61, 0x00,
	0x63, 0x00, 0x68, 0x00, 0x65, 0x00, 0x2d, 0x00, 0x53, 0x00, 0x79, 0x00, 0x73, 0x00, 0x74, 0x00,
	0x65, 0x00, 0x6d, 0x00, 0x2e, 0x00, 0x64, 0x00, 0x61, 0x00, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* Tests the libftxf_record_initialize function
 * Returns 1 if successful or 0 if not
 */
int ftxf_test_record_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libftxf_record_t *record        = NULL;
	int result                      = 0;

#if defined( HAVE_FTXF_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libftxf_record_initialize(
	          &record,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "record",
	 record );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libftxf_record_free(
	          &record,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libftxf_record_initialize(
	          NULL,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	record = (libftxf_record_t *) 0x12345678UL;

	result = libftxf_record_initialize(
	          &record,
	          &error );

	record = NULL;

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_FTXF_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libftxf_record_initialize with malloc failing
		 */
		ftxf_test_malloc_attempts_before_fail = test_number;

		result = libftxf_record_initialize(
		          &record,
		          &error );

		if( ftxf_test_malloc_attempts_before_fail != -1 )
		{
			ftxf_test_malloc_attempts_before_fail = -1;

			if( record != NULL )
			{
				libftxf_record_free(
				 &record,
				 NULL );
			}
		}
		else
		{
			FTXF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FTXF_TEST_ASSERT_IS_NULL(
			 "record",
			 record );

			FTXF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libftxf_record_initialize with memset failing
		 */
		ftxf_test_memset_attempts_before_fail = test_number;

		result = libftxf_record_initialize(
		          &record,
		          &error );

		if( ftxf_test_memset_attempts_before_fail != -1 )
		{
			ftxf_test_memset_attempts_before_fail = -1;

			if( record != NULL )
			{
				libftxf_record_free(
				 &record,
				 NULL );
			}
		}
		else
		{
			FTXF_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			FTXF_TEST_ASSERT_IS_NULL(
			 "record",
			 record );

			FTXF_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_FTXF_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( record != NULL )
	{
		libftxf_record_free(
		 &record,
		 NULL );
	}
	return( 0 );
}

/* Tests the libftxf_record_free function
 * Returns 1 if successful or 0 if not
 */
int ftxf_test_record_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libftxf_record_free(
	          NULL,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBFTXF_DLL_IMPORT )

/* Tests the libftxf_internal_record_read_update_journal_entry_list_data function
 * Returns 1 if successful or 0 if not
 */
int ftxf_test_internal_record_read_update_journal_entry_list_data(
     void )
{
	libcerror_error_t *error = NULL;
	libftxf_record_t *record = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libftxf_record_initialize(
	          &record,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "record",
	 record );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libftxf_internal_record_read_update_journal_entry_list_data(
	          (libftxf_internal_record_t *) record,
	          ftxf_test_record_data1,
	          208,
	          &error );

FTXF_TEST_FPRINT_ERROR( error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libftxf_internal_record_read_update_journal_entry_list_data(
	          (libftxf_internal_record_t *) record,
	          ftxf_test_record_data1,
	          208,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libftxf_internal_record_read_update_journal_entry_list_data(
	          NULL,
	          ftxf_test_record_data1,
	          208,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libftxf_internal_record_read_update_journal_entry_list_data(
	          (libftxf_internal_record_t *) record,
	          NULL,
	          208,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libftxf_internal_record_read_update_journal_entry_list_data(
	          (libftxf_internal_record_t *) record,
	          ftxf_test_record_data1,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Byte stream too small
	 */
	result = libftxf_internal_record_read_update_journal_entry_list_data(
	          (libftxf_internal_record_t *) record,
	          ftxf_test_record_data1,
	          0,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libftxf_record_free(
	          &record,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( record != NULL )
	{
		libftxf_record_free(
		 &record,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBFTXF_DLL_IMPORT ) */

/* Tests the libftxf_record_copy_from_byte_stream function
 * Returns 1 if successful or 0 if not
 */
int ftxf_test_record_copy_from_byte_stream(
     void )
{
	libcerror_error_t *error         = NULL;
	libftxf_record_t *record = NULL;
	int result                       = 0;

	/* Initialize test
	 */
	result = libftxf_record_initialize(
	          &record,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "record",
	 record );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libftxf_record_copy_from_byte_stream(
	          record,
	          ftxf_test_record_data1,
	          208,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Read the data twice to catch issues with previous set values
	 */
	result = libftxf_record_copy_from_byte_stream(
	          record,
	          ftxf_test_record_data1,
	          208,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libftxf_record_copy_from_byte_stream(
	          NULL,
	          ftxf_test_record_data1,
	          208,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libftxf_record_copy_from_byte_stream(
	          record,
	          NULL,
	          208,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libftxf_record_copy_from_byte_stream(
	          record,
	          ftxf_test_record_data1,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Byte stream too small
	 */
	result = libftxf_record_copy_from_byte_stream(
	          record,
	          ftxf_test_record_data1,
	          0,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	FTXF_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libftxf_record_free(
	          &record,
	          &error );

	FTXF_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	FTXF_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	FTXF_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( record != NULL )
	{
		libftxf_record_free(
		 &record,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc FTXF_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] FTXF_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc FTXF_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] FTXF_TEST_ATTRIBUTE_UNUSED )
#endif
{
	FTXF_TEST_UNREFERENCED_PARAMETER( argc )
	FTXF_TEST_UNREFERENCED_PARAMETER( argv )

	FTXF_TEST_RUN(
	 "libftxf_record_initialize",
	 ftxf_test_record_initialize );

	FTXF_TEST_RUN(
	 "libftxf_record_free",
	 ftxf_test_record_free );

#if defined( __GNUC__ ) && !defined( LIBFTXF_DLL_IMPORT )

	FTXF_TEST_RUN(
	 "libftxf_internal_record_read_update_journal_entry_list_data",
	 ftxf_test_internal_record_read_update_journal_entry_list_data );

#endif /* defined( __GNUC__ ) && !defined( LIBFTXF_DLL_IMPORT ) */

	FTXF_TEST_RUN(
	 "libftxf_record_copy_from_byte_stream",
	 ftxf_test_record_copy_from_byte_stream );

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

