/*
 * Copyright (c) 2005-2006 Alon Bar-Lev <alon.barlev@gmail.com>
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, or the OpenIB.org BSD license.
 *
 * GNU General Public License (GPL) Version 2
 * ===========================================
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program (see the file COPYING[.GPL2] included with this
 *  distribution); if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * OpenIB.org BSD license
 * =======================
 * Redistribution and use in source and binary forms, with or without modifi-
 * cation, are permitted provided that the following conditions are met:
 *
 *   o  Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *
 *   o  Redistributions in binary form must reproduce the above copyright no-
 *      tice, this list of conditions and the following disclaimer in the do-
 *      cumentation and/or other materials provided with the distribution.
 *
 *   o  The names of the contributors may not be used to endorse or promote
 *      products derived from this software without specific prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LI-
 * ABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUEN-
 * TIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEV-
 * ER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABI-
 * LITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file pkcs11h-token.h
 * @brief pkcs11-helper token interface.
 * @author Alon Bar-Lev <alon.barlev@gmail.com>
 */

#ifndef __PKCS11H_TOKEN_H
#define __PKCS11H_TOKEN_H

#include <pkcs11-helper-1.0/pkcs11h-core.h>

#if defined(__cplusplus)
extern "C" {
#endif

struct pkcs11h_token_id_list_s;

/**
 * @brief Token identifier list.
 */
typedef struct pkcs11h_token_id_list_s *pkcs11h_token_id_list_t;

/**
 * @brief Token identifier list.
 */
struct pkcs11h_token_id_list_s {
	/** Next element. */
	pkcs11h_token_id_list_t next;
	/** Token id element. */
	pkcs11h_token_id_t token_id;
};

/**
 * @brief Free token_id object.
 * @param token_id	Token reference.
 * @return CK_RV.
 */
CK_RV
pkcs11h_token_freeTokenId (
	IN pkcs11h_token_id_t token_id
);

/**
 * @brief Duplicate token_id object.
 * @param to		Target.
 * @param from		Source.
 * @return CK_RV.
 * @see pkcs11h_token_freeTokenId().
 */
CK_RV
pkcs11h_token_duplicateTokenId (
	OUT pkcs11h_token_id_t * const to,
	IN const pkcs11h_token_id_t from
);

/**
 * @brief Returns TRUE if same token id
 * @param a		a.
 * @param b		b.
 * @return TRUE if same token identifier.
 */
PKCS11H_BOOL
pkcs11h_token_sameTokenId (
	IN const pkcs11h_token_id_t a,
	IN const pkcs11h_token_id_t b
);

/**
 * @brief Force login, avoid hooks.
 * @param token_id	Token to login into.
 * @param readonly	Should session be readonly.
 * @param pin		PIN to login, NULL for protected authentication.
 * @return CK_RV.
 */
CK_RV
pkcs11h_token_login (
	IN const pkcs11h_token_id_t token_id,
	IN const PKCS11H_BOOL readonly,
	IN const char * const pin
);

/**
 * @brief Ensure token is accessible.
 * @brief token_id	Token id object.
 * @brief user_data	Optional user data, to be passed to hooks.
 * @brief mask_prompt	Allow prompt @ref PKCS11H_PROMPT_MASK.
 * @return CK_RV.
 */
CK_RV
pkcs11h_token_ensureAccess (
	IN const pkcs11h_token_id_t token_id,
	IN void * const user_data,
	IN const unsigned mask_prompt
);

/**
 * @brief Free certificate_id list.
 * @param token_id_list	List.
 * @return CK_RV.
 */
CK_RV
pkcs11h_token_freeTokenIdList (
	IN const pkcs11h_token_id_list_t token_id_list
);

/**
 * @brief Enumerate available tokens.
 * @param method		Enum method @ref PKCS11H_ENUM_METHOD.
 * @param p_token_id_list	List.
 * @return CK_RV.
 * @note Caller must free result.
 * @see pkcs11h_token_freeTokenIdList().
 */
CK_RV
pkcs11h_token_enumTokenIds (
	IN const int method,
	OUT pkcs11h_token_id_list_t * const p_token_id_list
);

/**
 * @brief Serialize token_id into string.
 * @param sz			Output string.
 * @param max			Maximum string size.
 * @param token_id		id to serialize
 * @return CK_RV.
 * @note sz may be NULL to get size.
 */
CK_RV
pkcs11h_token_serializeTokenId (
	OUT char * const sz,
	IN OUT size_t *max,
	IN const pkcs11h_token_id_t token_id
);

/**
 * @brief Deserialize token_id from string.
 * @param p_token_id		id.
 * @param sz			Input string.
 * @return CK_RV.
 * @note Caller must free result.
 * @see pkcs11h_token_freeTokenId().
 */
CK_RV
pkcs11h_token_deserializeTokenId (
	OUT pkcs11h_token_id_t *p_token_id,
	IN const char * const sz
);

#ifdef __cplusplus
}
#endif

#endif				/* __PKCS11H_TOKEN_H */