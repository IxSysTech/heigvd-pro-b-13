#include "config.h"

#define LIBSSH_STATIC

#include <sys/stat.h>
#include <fcntl.h>

#include "torture.h"
#include "torture_key.h"
#include "torture_pki.h"
#include "pki.c"

#define LIBSSH_ECDSA_TESTKEY "libssh_testkey.id_ecdsa"
#define LIBSSH_ECDSA_TESTKEY_PASSPHRASE "libssh_testkey_passphrase.id_ecdsa"

const char template[] = "temp_dir_XXXXXX";
const unsigned char ECDSA_HASH[] = "12345678901234567890";

struct pki_st {
    char *cwd;
    char *temp_dir;
    enum ssh_keytypes_e type;
};

static int setup_ecdsa_key(void **state, int ecdsa_bits)
{
    struct pki_st *test_state = NULL;
    char *cwd = NULL;
    char *tmp_dir = NULL;
    int rc = 0;

    test_state = (struct pki_st *)malloc(sizeof(struct pki_st));
    assert_non_null(test_state);

    cwd = torture_get_current_working_dir();
    assert_non_null(cwd);

    tmp_dir = torture_make_temp_dir(template);
    assert_non_null(tmp_dir);

    test_state->cwd = cwd;
    test_state->temp_dir = tmp_dir;

    *state = test_state;

    rc = torture_change_dir(tmp_dir);
    assert_int_equal(rc, 0);

    printf("Changed directory to: %s\n", tmp_dir);

    switch (ecdsa_bits) {
        case 521:
            test_state->type = SSH_KEYTYPE_ECDSA_P521;
            break;
        case 384:
            test_state->type = SSH_KEYTYPE_ECDSA_P384;
            break;
        default:
            test_state->type = SSH_KEYTYPE_ECDSA_P256;
            break;
    }

    torture_write_file(LIBSSH_ECDSA_TESTKEY,
                       torture_get_testkey(test_state->type, 0));
    torture_write_file(LIBSSH_ECDSA_TESTKEY_PASSPHRASE,
                       torture_get_testkey(test_state->type, 1));
    torture_write_file(LIBSSH_ECDSA_TESTKEY ".pub",
                       torture_get_testkey_pub(test_state->type));
    torture_write_file(LIBSSH_ECDSA_TESTKEY "-cert.pub",
                       torture_get_testkey_pub(test_state->type+3));
    return 0;
}

static int setup_openssh_ecdsa_key(void **state, int ecdsa_bits)
{
    struct pki_st *test_state = NULL;
    char *cwd = NULL;
    char *tmp_dir = NULL;
    const char *keystring = NULL;
    int rc = 0;

    test_state = (struct pki_st *)malloc(sizeof(struct pki_st));
    assert_non_null(test_state);

    cwd = torture_get_current_working_dir();
    assert_non_null(cwd);

    tmp_dir = torture_make_temp_dir(template);
    assert_non_null(tmp_dir);

    test_state->cwd = cwd;
    test_state->temp_dir = tmp_dir;

    *state = test_state;

    rc = torture_change_dir(tmp_dir);
    assert_int_equal(rc, 0);

    printf("Changed directory to: %s\n", tmp_dir);

    switch (ecdsa_bits) {
        case 521:
            test_state->type = SSH_KEYTYPE_ECDSA_P521;
            break;
        case 384:
            test_state->type = SSH_KEYTYPE_ECDSA_P384;
            break;
        default:
            test_state->type = SSH_KEYTYPE_ECDSA_P256;
            break;
    }

    keystring = torture_get_openssh_testkey(test_state->type, 0);
    torture_write_file(LIBSSH_ECDSA_TESTKEY, keystring);

    keystring = torture_get_openssh_testkey(test_state->type, 1);
    torture_write_file(LIBSSH_ECDSA_TESTKEY_PASSPHRASE, keystring);
    torture_write_file(LIBSSH_ECDSA_TESTKEY ".pub",
                       torture_get_testkey_pub(test_state->type));
    torture_write_file(LIBSSH_ECDSA_TESTKEY "-cert.pub",
                       torture_get_testkey_pub(test_state->type+3));
    return 0;
}

static int setup_ecdsa_key_521(void **state)
{
    setup_ecdsa_key(state, 521);

    return 0;
}

static int setup_ecdsa_key_384(void **state)
{
    setup_ecdsa_key(state, 384);

    return 0;
}

static int setup_ecdsa_key_256(void **state)
{
    setup_ecdsa_key(state, 256);

    return 0;
}

static int setup_openssh_ecdsa_key_521(void **state)
{
    setup_openssh_ecdsa_key(state, 521);

    return 0;
}

static int setup_openssh_ecdsa_key_384(void **state)
{
    setup_openssh_ecdsa_key(state, 384);

    return 0;
}

static int setup_openssh_ecdsa_key_256(void **state)
{
    setup_openssh_ecdsa_key(state, 256);

    return 0;
}

static int teardown(void **state) {

    struct pki_st *test_state = NULL;
    int rc = 0;

    test_state = *((struct pki_st **)state);

    assert_non_null(test_state);
    assert_non_null(test_state->cwd);
    assert_non_null(test_state->temp_dir);

    rc = torture_change_dir(test_state->cwd);
    assert_int_equal(rc, 0);

    rc = torture_rmdirs(test_state->temp_dir);
    assert_int_equal(rc, 0);

    SAFE_FREE(test_state->temp_dir);
    SAFE_FREE(test_state->cwd);
    SAFE_FREE(test_state);

    return 0;
}

static void torture_pki_ecdsa_import_pubkey_file(void **state)
{
    ssh_key pubkey = NULL;
    int rc;

    (void)state;

    /* The key doesn't have the hostname as comment after the key */
    rc = ssh_pki_import_pubkey_file(LIBSSH_ECDSA_TESTKEY ".pub", &pubkey);
    assert_return_code(rc, errno);
    assert_non_null(pubkey);

    SSH_KEY_FREE(pubkey);
}

static void torture_pki_ecdsa_import_pubkey_from_openssh_privkey(void **state)
{
    ssh_key pubkey = NULL;
    int rc;

    (void)state;

    /* The key doesn't have the hostname as comment after the key */
    rc = ssh_pki_import_pubkey_file(LIBSSH_ECDSA_TESTKEY_PASSPHRASE, &pubkey);
    assert_return_code(rc, errno);
    assert_non_null(pubkey);

    SSH_KEY_FREE(pubkey);
}

static void torture_pki_ecdsa_import_privkey_base64(void **state)
{
    int rc;
    char *key_str = NULL;
    ssh_key key = NULL;
    const char *passphrase = torture_get_testkey_passphrase();

    (void) state; /* unused */

    key_str = torture_pki_read_file(LIBSSH_ECDSA_TESTKEY);
    assert_non_null(key_str);

    rc = ssh_pki_import_privkey_base64(key_str, passphrase, NULL, NULL, &key);
    assert_true(rc == 0);
    assert_non_null(key);

    rc = ssh_key_is_private(key);
    assert_true(rc == 1);

    free(key_str);
    SSH_KEY_FREE(key);
}

static void torture_pki_ecdsa_publickey_from_privatekey(void **state)
{
    int rc;
    char *key_str = NULL;
    ssh_key key = NULL;
    ssh_key pubkey = NULL;
    const char *passphrase = NULL;

    (void) state; /* unused */

    key_str = torture_pki_read_file(LIBSSH_ECDSA_TESTKEY);
    assert_non_null(key_str);

    rc = ssh_pki_import_privkey_base64(key_str, passphrase, NULL, NULL, &key);
    assert_true(rc == 0);
    assert_non_null(key);

    rc = ssh_pki_export_privkey_to_pubkey(key, &pubkey);
    assert_true(rc == SSH_OK);
    assert_non_null(pubkey);

    free(key_str);
    SSH_KEY_FREE(key);
    SSH_KEY_FREE(pubkey);
}

static void torture_pki_ecdsa_import_cert_file(void **state)
{
    int rc;
    ssh_key cert = NULL;
    enum ssh_keytypes_e type;
    struct pki_st *test_state = *((struct pki_st **)state);

    rc = ssh_pki_import_cert_file(LIBSSH_ECDSA_TESTKEY "-cert.pub", &cert);
    assert_true(rc == 0);
    assert_non_null(cert);

    type = ssh_key_type(cert);
    assert_true(type == test_state->type+3);

    rc = ssh_key_is_public(cert);
    assert_true(rc == 1);

    SSH_KEY_FREE(cert);
}

static void torture_pki_ecdsa_publickey_base64(void **state)
{
    enum ssh_keytypes_e type;
    char *b64_key = NULL, *key_buf = NULL, *p = NULL;
    const char *q = NULL;
    ssh_key key = NULL;
    int rc;
    struct pki_st *test_state = *((struct pki_st **)state);

    key_buf = torture_pki_read_file(LIBSSH_ECDSA_TESTKEY ".pub");
    assert_non_null(key_buf);

    q = p = key_buf;
    while (p != NULL && *p != '\0' && *p != ' ') p++;
    if (p != NULL) {
        *p = '\0';
    }

    type = ssh_key_type_from_name(q);
    assert_true(type == test_state->type);

    q = ++p;
    while (p != NULL && *p != '\0' && *p != ' ') p++;
    if (p != NULL) {
        *p = '\0';
    }

    rc = ssh_pki_import_pubkey_base64(q, type, &key);
    assert_true(rc == 0);
    assert_non_null(key);

    rc = ssh_pki_export_pubkey_base64(key, &b64_key);
    assert_true(rc == 0);
    assert_non_null(b64_key);

    assert_string_equal(q, b64_key);

    free(b64_key);
    free(key_buf);
    SSH_KEY_FREE(key);
}

static void torture_pki_ecdsa_generate_pubkey_from_privkey(void **state)
{
    char pubkey_original[4096] = {0};
    char pubkey_generated[4096] = {0};
    ssh_key privkey = NULL;
    ssh_key pubkey = NULL;
    int rc;
    int len;

    (void) state; /* unused */

    rc = torture_read_one_line(LIBSSH_ECDSA_TESTKEY ".pub",
                               pubkey_original,
                               sizeof(pubkey_original));
    assert_true(rc == 0);

    /* remove the public key, generate it from the private key and write it. */
    unlink(LIBSSH_ECDSA_TESTKEY ".pub");

    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY,
                                     NULL,
                                     NULL,
                                     NULL,
                                     &privkey);
    assert_true(rc == 0);
    assert_non_null(privkey);

    rc = ssh_pki_export_privkey_to_pubkey(privkey, &pubkey);
    assert_true(rc == SSH_OK);
    assert_non_null(pubkey);

    rc = ssh_pki_export_pubkey_file(pubkey, LIBSSH_ECDSA_TESTKEY ".pub");
    assert_true(rc == 0);

    rc = torture_read_one_line(LIBSSH_ECDSA_TESTKEY ".pub",
                               pubkey_generated,
                               sizeof(pubkey_generated));
    assert_true(rc == 0);
    len = torture_pubkey_len(pubkey_original);
    assert_int_equal(strncmp(pubkey_original, pubkey_generated, len), 0);

    SSH_KEY_FREE(privkey);
    SSH_KEY_FREE(pubkey);
}

static void torture_pki_ecdsa_duplicate_key(void **state)
{
    int rc;
    char *b64_key = NULL;
    char *b64_key_gen = NULL;
    ssh_key pubkey = NULL;
    ssh_key privkey = NULL;
    ssh_key privkey_dup = NULL;

    (void) state;

    rc = ssh_pki_import_pubkey_file(LIBSSH_ECDSA_TESTKEY ".pub", &pubkey);
    assert_true(rc == 0);
    assert_non_null(pubkey);

    rc = ssh_pki_export_pubkey_base64(pubkey, &b64_key);
    assert_true(rc == 0);
    SSH_KEY_FREE(pubkey);
    assert_non_null(b64_key);

    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY,
                                     NULL,
                                     NULL,
                                     NULL,
                                     &privkey);
    assert_true(rc == 0);
    assert_non_null(privkey);

    privkey_dup = ssh_key_dup(privkey);
    assert_non_null(privkey_dup);

    rc = ssh_pki_export_privkey_to_pubkey(privkey, &pubkey);
    assert_true(rc == SSH_OK);
    assert_non_null(pubkey);

    rc = ssh_pki_export_pubkey_base64(pubkey, &b64_key_gen);
    assert_true(rc == 0);
    assert_non_null(b64_key_gen);

    assert_string_equal(b64_key, b64_key_gen);

    rc = ssh_key_cmp(privkey, privkey_dup, SSH_KEY_CMP_PRIVATE);
    assert_true(rc == 0);

    SSH_KEY_FREE(pubkey);
    SSH_KEY_FREE(privkey);
    SSH_KEY_FREE(privkey_dup);
    SSH_STRING_FREE_CHAR(b64_key);
    SSH_STRING_FREE_CHAR(b64_key_gen);
}

/* Test case for bug #147: Private ECDSA key duplication did not carry
 * over parts of the key that then caused subsequent key demotion to
 * fail.
 */
static void torture_pki_ecdsa_duplicate_then_demote(void **state)
{
    ssh_key pubkey = NULL;
    ssh_key privkey = NULL;
    ssh_key privkey_dup = NULL;
    int rc;

    (void) state;

    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY,
                                     NULL,
                                     NULL,
                                     NULL,
                                     &privkey);
    assert_int_equal(rc, 0);
    assert_non_null(privkey);

    privkey_dup = ssh_key_dup(privkey);
    assert_non_null(privkey_dup);
    assert_int_equal(privkey->ecdsa_nid, privkey_dup->ecdsa_nid);

    rc = ssh_pki_export_privkey_to_pubkey(privkey_dup, &pubkey);
    assert_int_equal(rc, 0);
    assert_non_null(pubkey);
    assert_int_equal(pubkey->ecdsa_nid, privkey->ecdsa_nid);

    SSH_KEY_FREE(pubkey);
    SSH_KEY_FREE(privkey);
    SSH_KEY_FREE(privkey_dup);
}

static void torture_pki_generate_key_ecdsa(void **state)
{
    int rc;
    ssh_key key = NULL;
    ssh_signature sign = NULL;
    enum ssh_keytypes_e type = SSH_KEYTYPE_UNKNOWN;
    const char *type_char = NULL;
    const char *etype_char = NULL;
    ssh_session session=ssh_new();
    (void) state;

    rc = ssh_pki_generate(SSH_KEYTYPE_ECDSA_P256, 0, &key);
    assert_true(rc == SSH_OK);
    assert_non_null(key);
    sign = pki_do_sign(key, ECDSA_HASH, 20);
    assert_non_null(sign);
    rc = pki_signature_verify(session,sign,key,ECDSA_HASH,20);
    assert_true(rc == SSH_OK);
    type = ssh_key_type(key);
    assert_true(type == SSH_KEYTYPE_ECDSA_P256);
    type_char = ssh_key_type_to_char(type);
    assert_true(strcmp(type_char, "ecdsa-sha2-nistp256") == 0);
    etype_char = ssh_pki_key_ecdsa_name(key);
    assert_true(strcmp(etype_char, "ecdsa-sha2-nistp256") == 0);

    ssh_signature_free(sign);
    SSH_KEY_FREE(key);

    /* deprecated */
    rc = ssh_pki_generate(SSH_KEYTYPE_ECDSA, 256, &key);
    assert_true(rc == SSH_OK);
    assert_non_null(key);
    sign = pki_do_sign(key, ECDSA_HASH, 20);
    assert_non_null(sign);
    rc = pki_signature_verify(session,sign,key,ECDSA_HASH,20);
    assert_true(rc == SSH_OK);
    type = ssh_key_type(key);
    assert_true(type == SSH_KEYTYPE_ECDSA_P256);
    type_char = ssh_key_type_to_char(type);
    assert_true(strcmp(type_char, "ecdsa-sha2-nistp256") == 0);
    etype_char = ssh_pki_key_ecdsa_name(key);
    assert_true(strcmp(etype_char, "ecdsa-sha2-nistp256") == 0);

    ssh_signature_free(sign);
    SSH_KEY_FREE(key);

    rc = ssh_pki_generate(SSH_KEYTYPE_ECDSA_P384, 0, &key);
    assert_true(rc == SSH_OK);
    assert_non_null(key);
    sign = pki_do_sign(key, ECDSA_HASH, 20);
    assert_non_null(sign);
    rc = pki_signature_verify(session,sign,key,ECDSA_HASH,20);
    assert_true(rc == SSH_OK);
    type = ssh_key_type(key);
    assert_true(type == SSH_KEYTYPE_ECDSA_P384);
    type_char = ssh_key_type_to_char(type);
    assert_true(strcmp(type_char, "ecdsa-sha2-nistp384") == 0);
    etype_char =ssh_pki_key_ecdsa_name(key);
    assert_true(strcmp(etype_char, "ecdsa-sha2-nistp384") == 0);

    ssh_signature_free(sign);
    SSH_KEY_FREE(key);

    /* deprecated */
    rc = ssh_pki_generate(SSH_KEYTYPE_ECDSA, 384, &key);
    assert_true(rc == SSH_OK);
    assert_non_null(key);
    sign = pki_do_sign(key, ECDSA_HASH, 20);
    assert_non_null(sign);
    rc = pki_signature_verify(session,sign,key,ECDSA_HASH,20);
    assert_true(rc == SSH_OK);
    type = ssh_key_type(key);
    assert_true(type == SSH_KEYTYPE_ECDSA_P384);
    type_char = ssh_key_type_to_char(type);
    assert_true(strcmp(type_char, "ecdsa-sha2-nistp384") == 0);
    etype_char =ssh_pki_key_ecdsa_name(key);
    assert_true(strcmp(etype_char, "ecdsa-sha2-nistp384") == 0);

    ssh_signature_free(sign);
    SSH_KEY_FREE(key);

    rc = ssh_pki_generate(SSH_KEYTYPE_ECDSA_P521, 0, &key);
    assert_true(rc == SSH_OK);
    assert_non_null(key);
    sign = pki_do_sign(key, ECDSA_HASH, 20);
    assert_non_null(sign);
    rc = pki_signature_verify(session,sign,key,ECDSA_HASH,20);
    assert_true(rc == SSH_OK);
    type = ssh_key_type(key);
    assert_true(type == SSH_KEYTYPE_ECDSA_P521);
    type_char = ssh_key_type_to_char(type);
    assert_true(strcmp(type_char, "ecdsa-sha2-nistp521") == 0);
    etype_char =ssh_pki_key_ecdsa_name(key);
    assert_true(strcmp(etype_char, "ecdsa-sha2-nistp521") == 0);

    ssh_signature_free(sign);
    SSH_KEY_FREE(key);

    /* deprecated */
    rc = ssh_pki_generate(SSH_KEYTYPE_ECDSA, 521, &key);
    assert_true(rc == SSH_OK);
    assert_non_null(key);
    sign = pki_do_sign(key, ECDSA_HASH, 20);
    assert_non_null(sign);
    rc = pki_signature_verify(session,sign,key,ECDSA_HASH,20);
    assert_true(rc == SSH_OK);
    type = ssh_key_type(key);
    assert_true(type == SSH_KEYTYPE_ECDSA_P521);
    type_char = ssh_key_type_to_char(type);
    assert_true(strcmp(type_char, "ecdsa-sha2-nistp521") == 0);
    etype_char =ssh_pki_key_ecdsa_name(key);
    assert_true(strcmp(etype_char, "ecdsa-sha2-nistp521") == 0);

    ssh_signature_free(sign);
    SSH_KEY_FREE(key);

    ssh_free(session);
}

static void torture_pki_ecdsa_cert_verify(void **state)
{
    int rc;
    ssh_key privkey = NULL, cert = NULL;
    ssh_signature sign = NULL;
    ssh_session session=ssh_new();
    (void) state;

    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY,
                                     NULL,
                                     NULL,
                                     NULL,
                                     &privkey);
    assert_true(rc == 0);
    assert_non_null(privkey);

    rc = ssh_pki_import_cert_file(LIBSSH_ECDSA_TESTKEY "-cert.pub", &cert);
    assert_true(rc == 0);
    assert_non_null(cert);

    sign = pki_do_sign(privkey, ECDSA_HASH, 20);
    assert_non_null(sign);
    rc = pki_signature_verify(session, sign, cert, ECDSA_HASH, 20);
    assert_true(rc == SSH_OK);
    ssh_signature_free(sign);
    SSH_KEY_FREE(privkey);
    SSH_KEY_FREE(cert);

    ssh_free(session);
}

#ifdef HAVE_LIBCRYPTO
static void torture_pki_ecdsa_write_privkey(void **state)
{
    ssh_key origkey = NULL;
    ssh_key privkey = NULL;
    int rc;

    (void) state; /* unused */

    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY,
                                     NULL,
                                     NULL,
                                     NULL,
                                     &origkey);
    assert_true(rc == 0);
    assert_non_null(origkey);

    unlink(LIBSSH_ECDSA_TESTKEY);

    rc = ssh_pki_export_privkey_file(origkey,
                                     NULL,
                                     NULL,
                                     NULL,
                                     LIBSSH_ECDSA_TESTKEY);
    assert_true(rc == 0);

    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY,
                                     NULL,
                                     NULL,
                                     NULL,
                                     &privkey);
    assert_true(rc == 0);
    assert_non_null(privkey);

    rc = ssh_key_cmp(origkey, privkey, SSH_KEY_CMP_PRIVATE);
    assert_true(rc == 0);

    SSH_KEY_FREE(origkey);
    SSH_KEY_FREE(privkey);

    /* Test with passphrase */
    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY_PASSPHRASE,
                                     torture_get_testkey_passphrase(),
                                     NULL,
                                     NULL,
                                     &origkey);
    assert_true(rc == 0);
    assert_non_null(origkey);

    unlink(LIBSSH_ECDSA_TESTKEY_PASSPHRASE);
    rc = ssh_pki_export_privkey_file(origkey,
                                     torture_get_testkey_passphrase(),
                                     NULL,
                                     NULL,
                                     LIBSSH_ECDSA_TESTKEY_PASSPHRASE);
    assert_true(rc == 0);

    /* Test with invalid passphrase */
    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY_PASSPHRASE,
                                     "invalid secret",
                                     NULL,
                                     NULL,
                                     &privkey);
    assert_true(rc == SSH_ERROR);
    assert_null(privkey);

    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY_PASSPHRASE,
                                     torture_get_testkey_passphrase(),
                                     NULL,
                                     NULL,
                                     &privkey);
    assert_true(rc == 0);
    assert_non_null(privkey);

    rc = ssh_key_cmp(origkey, privkey, SSH_KEY_CMP_PRIVATE);
    assert_true(rc == 0);

    SSH_KEY_FREE(origkey);
    SSH_KEY_FREE(privkey);
}
#endif /* HAVE_LIBCRYPTO */

static void torture_pki_ecdsa_name(void **state, const char *expected_name)
{
    int rc;
    ssh_key key = NULL;
    const char *etype_char = NULL;

    (void) state; /* unused */

    rc = ssh_pki_import_privkey_file(LIBSSH_ECDSA_TESTKEY, NULL, NULL, NULL, &key);
    assert_true(rc == 0);
    assert_non_null(key);

    etype_char =ssh_pki_key_ecdsa_name(key);
    assert_true(strcmp(etype_char, expected_name) == 0);

    SSH_KEY_FREE(key);
}

static void torture_pki_ecdsa_name256(void **state)
{
    torture_pki_ecdsa_name(state, "ecdsa-sha2-nistp256");
}

static void torture_pki_ecdsa_name384(void **state)
{
    torture_pki_ecdsa_name(state, "ecdsa-sha2-nistp384");
}

static void torture_pki_ecdsa_name521(void **state)
{
    torture_pki_ecdsa_name(state, "ecdsa-sha2-nistp521");
}

int torture_run_tests(void) {
    int rc;
    struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_pubkey_file,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_pubkey_file,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_pubkey_file,
                                        setup_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_pubkey_from_openssh_privkey,
                                        setup_openssh_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_pubkey_from_openssh_privkey,
                                        setup_openssh_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_pubkey_file,
                                        setup_openssh_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_privkey_base64,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_privkey_base64,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_privkey_base64,
                                        setup_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_privkey_base64,
                                        setup_openssh_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_privkey_base64,
                                        setup_openssh_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_privkey_base64,
                                        setup_openssh_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_publickey_from_privatekey,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_publickey_from_privatekey,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_publickey_from_privatekey,
                                        setup_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_cert_file,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_cert_file,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_import_cert_file,
                                        setup_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_duplicate_then_demote,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_duplicate_then_demote,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_duplicate_then_demote,
                                        setup_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_publickey_base64,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_publickey_base64,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_publickey_base64,
                                        setup_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_generate_pubkey_from_privkey,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_generate_pubkey_from_privkey,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_generate_pubkey_from_privkey,
                                        setup_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_duplicate_key,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_duplicate_key,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_duplicate_key,
                                        setup_ecdsa_key_521,
                                        teardown),
        cmocka_unit_test(torture_pki_generate_key_ecdsa),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_cert_verify,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_cert_verify,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_cert_verify,
                                        setup_ecdsa_key_521,
                                        teardown),
#ifdef HAVE_LIBCRYPTO
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_write_privkey,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_write_privkey,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_write_privkey,
                                        setup_ecdsa_key_521,
                                        teardown),
#endif /* HAVE_LIBCRYPTO */
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_name256,
                                        setup_ecdsa_key_256,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_name384,
                                        setup_ecdsa_key_384,
                                        teardown),
        cmocka_unit_test_setup_teardown(torture_pki_ecdsa_name521,
                                        setup_ecdsa_key_521,
                                        teardown),
    };

    ssh_init();
    torture_filter_tests(tests);
    rc = cmocka_run_group_tests(tests, NULL, NULL);
    ssh_finalize();
    return rc;
}
