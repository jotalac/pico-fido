/*
 * This file is part of a combined Pico FIDO + Pico OpenPGP firmware.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Replacements for the parts of pico-openpgp this firmware leaves out:
 *
 * - Vault backup: pico-fido and pico-openpgp both keep their vault in EF_VAULT_KEY,
 *   so only FIDO's vault stays active. GPG keys cannot be exported through it.
 * - PIV: a separate smartcard app that is not needed for GPG.
 */

#include "openpgp.h"
#include "openpgp_vault.h"

bool openpgp_vault_is_enrolled(void) {
    return false;
}

bool openpgp_vault_wrapper_available(openpgp_vault_app_t app) {
    (void) app;
    return false;
}

int openpgp_vault_load_kvault(openpgp_vault_app_t app, uint8_t kvault[OPENPGP_VAULT_KEY_SIZE]) {
    (void) app;
    (void) kvault;
    return PICOKEYS_ERR_FILE_NOT_FOUND;
}

int openpgp_vault_store_kvault(openpgp_vault_app_t app, const uint8_t kvault[OPENPGP_VAULT_KEY_SIZE]) {
    (void) app;
    (void) kvault;
    return PICOKEYS_EXEC_ERROR;
}

/* Nothing to clear, and FIDO's vault in the shared file must survive a GPG reset. */
int openpgp_vault_clear_openpgp(void) {
    return PICOKEYS_OK;
}

int openpgp_vault_clear_wrappers(void) {
    return PICOKEYS_OK;
}

bool openpgp_vault_backup_authorized(openpgp_vault_app_t app) {
    (void) app;
    return false;
}

int openpgp_vault_command(openpgp_vault_app_t app) {
    (void) app;
    return SW_INS_NOT_SUPPORTED();
}

/* The PIV PIN can never be verified because the PIV app is not built. */
bool has_pwpiv = false;
uint8_t session_pwpiv[32];

int cmd_openpgp_vault(void) {
    return openpgp_vault_command(OPENPGP_VAULT_APP_OPENPGP);
}

bool piv_key_operation_authorized(uint16_t operation, bool internal_firmware) {
    (void) operation;
    (void) internal_firmware;
    return false;
}

extern int piv_parse_discovery(const file_t *ef);
int piv_parse_discovery(const file_t *ef) {
    (void) ef;
    return 0;
}
