/*
 * Record functions
 *
 * Copyright (C) 2010-2021, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFTXF_INTERNAL_RECORD_H )
#define _LIBFTXF_INTERNAL_RECORD_H

#include <common.h>
#include <types.h>

#include "libftxf_extern.h"
#include "libftxf_libcerror.h"
#include "libftxf_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libftxf_internal_record libftxf_internal_record_t;

struct libftxf_internal_record
{
	/* The size
	 */
	uint32_t size;
};

LIBFTXF_EXTERN \
int libftxf_record_initialize(
     libftxf_record_t **txf_record,
     libcerror_error_t **error );

LIBFTXF_EXTERN \
int libftxf_record_free(
     libftxf_record_t **txf_record,
     libcerror_error_t **error );

int libftxf_internal_record_read_update_journal_entry_list_data(
     libftxf_internal_record_t *internal_record,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

LIBFTXF_EXTERN \
int libftxf_record_copy_from_byte_stream(
     libftxf_record_t *txf_record,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFTXF_INTERNAL_RECORD_H ) */

