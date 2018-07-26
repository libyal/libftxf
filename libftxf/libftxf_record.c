/*
 * Record functions
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libftxf_debug.h"
#include "libftxf_definitions.h"
#include "libftxf_libcerror.h"
#include "libftxf_libcnotify.h"
#include "libftxf_libfdatetime.h"
#include "libftxf_libfguid.h"
#include "libftxf_libfusn.h"
#include "libftxf_libuna.h"
#include "libftxf_record.h"

#include "ftxf_record.h"

/* Creates a record
 * Make sure the value record is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libftxf_record_initialize(
     libftxf_record_t **record,
     libcerror_error_t **error )
{
	libftxf_internal_record_t *internal_record = NULL;
	static char *function                      = "libftxf_record_initialize";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record.",
		 function );

		return( -1 );
	}
	if( *record != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid record value already set.",
		 function );

		return( -1 );
	}
	internal_record = memory_allocate_structure(
	                   libftxf_internal_record_t );

	if( internal_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create record.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_record,
	     0,
	     sizeof( libftxf_internal_record_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear record.",
		 function );

		goto on_error;
	}
	*record = (libftxf_record_t *) internal_record;

	return( 1 );

on_error:
	if( internal_record != NULL )
	{
		memory_free(
		 internal_record );
	}
	return( -1 );
}

/* Frees a record
 * Returns 1 if successful or -1 on error
 */
int libftxf_record_free(
     libftxf_record_t **record,
     libcerror_error_t **error )
{
	libftxf_internal_record_t *internal_record = NULL;
	static char *function                      = "libftxf_record_free";

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record.",
		 function );

		return( -1 );
	}
	if( *record != NULL )
	{
		internal_record = (libftxf_internal_record_t *) *record;
		*record         = NULL;

		memory_free(
		 internal_record );
	}
	return( 1 );
}

/* Reads the update journal entry list
 * Returns 1 if successful or -1 on error
 */
int libftxf_internal_record_read_update_journal_entry_list_data(
     libftxf_internal_record_t *internal_record,
     const uint8_t *record_data,
     size_t record_data_size,
     libcerror_error_t **error )
{
	libfusn_record_t *usn_record              = NULL;
	static char *function                     = "libftxf_internal_record_read_update_journal_entry_list_data";
	size_t record_data_offset                 = 0;
	uint64_t record_chain_next_lsn            = 0;
	uint32_t update_journal_entry_list_offset = 0;
	uint32_t update_journal_entry_list_size   = 0;
	uint32_t usn_record_size                  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit                      = 0;
#endif

	if( internal_record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal record.",
		 function );

		return( -1 );
	}
	if( record_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record data.",
		 function );

		return( -1 );
	}
	if( record_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid record data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( record_data_size < ( sizeof( ftxf_record_header_t ) + 16 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid record data value too small.",
		 function );

		return( -1 );
	}
	record_data_offset = sizeof( ftxf_record_header_t );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: journal entry list data:\n",
		 function );
		libcnotify_print_data(
		 &( record_data[ record_data_offset ] ),
		 16,
		 0 );
	}
#endif
	byte_stream_copy_to_uint64_little_endian(
	 &( record_data[ record_data_offset ] ),
	 record_chain_next_lsn );

	record_data_offset += 8;

	byte_stream_copy_to_uint32_little_endian(
	 &( record_data[ record_data_offset ] ),
	 update_journal_entry_list_offset );

	record_data_offset += 4;

	byte_stream_copy_to_uint32_little_endian(
	 &( record_data[ record_data_offset ] ),
	 update_journal_entry_list_size );

	record_data_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: next record lsn\t\t: 0x%08" PRIx64 "\n",
		 function,
		 record_chain_next_lsn );

		libcnotify_printf(
		 "%s: list entries offset\t: 0x%08" PRIx32 "\n",
		 function,
		 update_journal_entry_list_offset );

		libcnotify_printf(
		 "%s: list entries size\t\t: %" PRIu32 "\n",
		 function,
		 update_journal_entry_list_size );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( ( (size_t) update_journal_entry_list_offset < record_data_offset )
	 || ( (size_t) update_journal_entry_list_offset > record_data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: update journal entry list offset value out of bounds.",
		 function );

		goto on_error;
	}
	if( ( (size_t) update_journal_entry_list_offset + (size_t) update_journal_entry_list_size ) < record_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: update journal entry list size value out of bounds.",
		 function );

		goto on_error;
	}
	if( (size_t) update_journal_entry_list_offset > record_data_offset )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: update journal entry list trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( record_data[ record_data_offset ] ),
			 (size_t) update_journal_entry_list_offset - record_data_offset,
			 0 );
		}
#endif
		record_data_offset = (size_t) update_journal_entry_list_offset;
	}
	while( record_data_offset < record_data_size )
	{
/* TODO print entry number */

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: unknown:\n",
			 function );
			libcnotify_print_data(
			 &( record_data[ record_data_offset ] ),
			 8,
			 0 );
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 &( record_data[ record_data_offset ] ),
			 value_64bit );
			libcnotify_printf(
			 "%s: unknown\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );
		}
#endif
		record_data_offset += 8;

		if( libfusn_record_initialize(
		     &usn_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create USN record.",
			 function );

			goto on_error;
		}
		if( libfusn_record_copy_from_byte_stream(
		     usn_record,
		     &( record_data[ record_data_offset ] ),
		     record_data_size - record_data_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read USN record.",
			 function );

			goto on_error;
		}
		if( libfusn_record_get_size(
		     usn_record,
		     &usn_record_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve USN record size.",
			 function );

			goto on_error;
		}
		record_data_offset += (size_t) usn_record_size;

/* TODO do something with USN records */
		if( libfusn_record_free(
		     &usn_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free USN record.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( usn_record != NULL )
	{
		libfusn_record_free(
		 &usn_record,
		 NULL );
	}
	return( -1 );
}

/* Copies the record from the byte stream
 * Returns 1 if successful or -1 on error
 */
int libftxf_record_copy_from_byte_stream(
     libftxf_record_t *record,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     libcerror_error_t **error )
{
	libftxf_internal_record_t *internal_record = NULL;
	static char *function                      = "libftxf_record_read";
	size_t byte_stream_offset                  = 0;
	uint16_t record_type                       = 0;
	uint16_t name_offset                       = 0;
	uint16_t name_size                         = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit                       = 0;
	uint32_t value_32bit                       = 0;
	uint16_t value_16bit                       = 0;
#endif

	if( record == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid record.",
		 function );

		return( -1 );
	}
	internal_record = (libftxf_internal_record_t *) record;

	if( byte_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid byte stream size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( byte_stream_size < sizeof( ftxf_record_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid byte stream value too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: record header data:\n",
		 function );
		libcnotify_print_data(
		 byte_stream,
		 sizeof( ftxf_record_header_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint16_little_endian(
	 ( (ftxf_record_header_t *) byte_stream )->record_type,
	 record_type );

	byte_stream_copy_to_uint32_little_endian(
	 ( (ftxf_record_header_t *) byte_stream )->record_size,
	 internal_record->size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (ftxf_record_header_t *) byte_stream )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: record type\t\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 record_type );

		byte_stream_copy_to_uint16_little_endian(
		 ( (ftxf_record_header_t *) byte_stream )->unknown2,
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (ftxf_record_header_t *) byte_stream )->file_identifier,
		 value_64bit );
		libcnotify_printf(
		 "%s: file identifier\t\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (ftxf_record_header_t *) byte_stream )->file_reference,
		 value_64bit );
		libcnotify_printf(
		 "%s: file reference\t\t\t\t\t: MFT entry: %" PRIu64 ", sequence: %" PRIu64 "\n",
		 function,
		 value_64bit & 0xffffffffffffUL,
		 value_64bit >> 48 );

		byte_stream_copy_to_uint32_little_endian(
		 ( (ftxf_record_header_t *) byte_stream )->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (ftxf_record_header_t *) byte_stream )->unknown5,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( libftxf_debug_print_guid_value(
		     function,
		     "unknown6 guid\t\t\t\t\t",
		     ( (ftxf_record_header_t *) byte_stream )->unknown6,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			return( -1 );
		}
		byte_stream_copy_to_uint64_little_endian(
		 ( (ftxf_record_header_t *) byte_stream )->unknown7,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown7\t\t\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( libftxf_debug_print_filetime_value(
		     function,
		     "unknown8 filetime\t\t\t\t\t",
		     ( (ftxf_record_header_t *) byte_stream )->unknown8,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print FILETIME value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "%s: record size\t\t\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_record->size );

		byte_stream_copy_to_uint32_little_endian(
		 ( (ftxf_record_header_t *) byte_stream )->unknown9,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown9\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint64_little_endian(
		 ( (ftxf_record_header_t *) byte_stream )->unknown10,
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown10\t\t\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	byte_stream_offset = sizeof( ftxf_record_header_t );

	if( ( (size_t) internal_record->size < sizeof( ftxf_record_header_t ) )
	 || ( (size_t) internal_record->size > byte_stream_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: record size value out of bounds.",
		 function );

		return( -1 );
	}
	switch( record_type )
	{
		case LIBFTXF_RECORD_TYPE_UPDATE_JOURNAL_ENTRIES_LIST:
			if( libftxf_internal_record_read_update_journal_entry_list_data(
			     internal_record,
			     byte_stream,
			     (size_t) internal_record->size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read update journal entry list.",
				 function );

				return( -1 );
			}
			break;

		default:
			break;
	}
/* TODO refactor */
	if( record_type == LIBFTXF_RECORD_TYPE_UPDATE_JOURNAL_ENTRIES_LIST )
	{
		return( 1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: record data:\n",
		 function );
		libcnotify_print_data(
		 &( byte_stream[ byte_stream_offset ] ),
		 (size_t) internal_record->size - sizeof( ftxf_record_header_t ),
		 0 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint64_little_endian(
		 &( byte_stream[ byte_stream_offset ] ),
		 value_64bit );
		libcnotify_printf(
		 "%s: unknown11\t\t\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );
	}
#endif
	byte_stream_offset += 8;

	if( record_type != 0x00 )
	{
		byte_stream_copy_to_uint16_little_endian(
		 &( byte_stream[ byte_stream_offset ] ),
		 name_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: name size\t\t\t\t\t\t: %" PRIu16 "\n",
			 function,
			 name_size );
		}
#endif
		byte_stream_offset += 2;

		name_size *= 2;

		byte_stream_copy_to_uint16_little_endian(
		 &( byte_stream[ byte_stream_offset ] ),
		 name_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: name offset\t\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 name_offset );
		}
#endif
		byte_stream_offset += 2;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 &( byte_stream[ byte_stream_offset ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown13\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
#endif
		byte_stream_offset += 4;
	}
	if( record_type == 0x02 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "...\n\n" );
		}
#endif
/* TODO print debug */
		byte_stream_offset += 24;
	}
	if( ( record_type == 0x02 )
	 || ( record_type == 0x07 ) )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libftxf_debug_print_filetime_value(
			     function,
			     "creation time\t\t\t\t\t",
			     &( byte_stream[ byte_stream_offset ] ),
			     8,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print FILETIME value.",
				 function );

				return( -1 );
			}
		}
#endif
		byte_stream_offset += 8;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libftxf_debug_print_filetime_value(
			     function,
			     "modification time\t\t\t\t\t",
			     &( byte_stream[ byte_stream_offset ] ),
			     8,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print FILETIME value.",
				 function );

				return( -1 );
			}
		}
#endif
		byte_stream_offset += 8;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libftxf_debug_print_filetime_value(
			     function,
			     "entry modification time\t\t\t\t",
			     &( byte_stream[ byte_stream_offset ] ),
			     8,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print FILETIME value.",
				 function );

				return( -1 );
			}
		}
#endif
		byte_stream_offset += 8;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libftxf_debug_print_filetime_value(
			     function,
			     "access time\t\t\t\t\t",
			     &( byte_stream[ byte_stream_offset ] ),
			     8,
			     LIBFDATETIME_ENDIAN_LITTLE,
			     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print FILETIME value.",
				 function );

				return( -1 );
			}
		}
#endif
		byte_stream_offset += 8;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 &( byte_stream[ byte_stream_offset ] ),
			 value_64bit );
			libcnotify_printf(
			 "%s: allocated file size\t\t\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );
		}
#endif
		byte_stream_offset += 8;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 &( byte_stream[ byte_stream_offset ] ),
			 value_64bit );
			libcnotify_printf(
			 "%s: file size\t\t\t\t\t\t: %" PRIu64 "\n",
			 function,
			 value_64bit );
		}
#endif
		byte_stream_offset += 8;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 &( byte_stream[ byte_stream_offset ] ),
			 value_32bit );
			libcnotify_printf(
			 "%s: file attribute flags\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
			libftxf_debug_print_file_attribute_flags(
			 value_32bit );
			libcnotify_printf(
			 "\n" );
		}
#endif
		byte_stream_offset += 4;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "...\n\n" );
		}
#endif
	}
	else if( record_type == 0x0b )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 &( byte_stream[ byte_stream_offset ] ),
			 value_64bit );
			libcnotify_printf(
			 "%s: unknown14\t\t\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );
		}
#endif
		byte_stream_offset += 8;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	else if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "...\n\n" );
	}
#endif
	if( record_type == 0x15 )
	{
		return( 1 );
	}
	if( name_size > 0 )
	{
		/* TODO check if name size is within bounds */
		/* TODO check if name offset is within bounds */

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libftxf_debug_print_utf16_string_value(
			     function,
			     "name\t\t\t\t\t\t",
			     &( byte_stream[ name_offset ] ),
			     name_size,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print UTF-16 string value.",
				 function );

				return( -1 );
			}
		}
#endif
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

