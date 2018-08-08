
#include <stdio.h>
#include <ldap.h>

#define HOSTNAME "ldap://10.1.108.54:389"
#define ROOT_DN "cn=Manager,dc=whgd,dc=com"
#define FIND_DN "dc=whgd,dc=com"

int main()
{
    int ldresult = 1;
    LDAP * ld = NULL;
    LDAPMessage *result, *e;
    BerElement *ber;
	int version;

    char *a, *strDN;
    struct berval **vals;
    int i, rc;
	
	ldresult = ldap_initialize(&ld, HOSTNAME);
	if (LDAP_SUCCESS != ldresult)
	{
		perror("ldap_initialize");
		return 1;
	}

	version = LDAP_VERSION3;
	ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &version);

    rc = ldap_simple_bind_s(ld, ROOT_DN, "secret");
    if (LDAP_SUCCESS != rc)
    {
        fprintf(stderr, "ldap_simple_bind_s: %s\n", ldap_err2string(rc));
        return 1;
    }

    if ((rc = ldap_search_ext_s(ld, FIND_DN, LDAP_SCOPE_SUB, 
			//"(&(cmmac2=XN:00:10:5)(objectclass=*))", 
            "(objectclass=*)",
			NULL, 0, NULL, NULL, LDAP_NO_LIMIT, LDAP_NO_LIMIT, &result)) != LDAP_SUCCESS)
    {
        fprintf(stderr, "ldap_search_ext_s: %s\n", ldap_err2string(rc));
        return 1;
    }

    e = ldap_first_entry(ld, result);
    if (NULL == e)
    {
        printf("no record is Found\n");
        return 1;
    }

    for (; e!= NULL; e = ldap_next_entry(ld, e))
    {
        strDN = ldap_get_dn(ld, e);
        printf("***************************************");
        printf("Attributes of %s: \n", strDN);
        ldap_memfree(strDN);

        for (a = ldap_first_attribute(ld, e, &ber); a != NULL; a = ldap_next_attribute(ld, e, ber))
        {
            if ((vals = ldap_get_values_len(ld, e, a)) != NULL)
            {
                for (i = 0; vals[i] != NULL; i++)
                    printf("a = %s: vals = %s, len = %d\n", a, vals[i]->bv_val, sizeof(vals[i]->bv_len));
                ber_bvecfree(vals);
            }
            ldap_memfree(a);
        }
    }

    if (ber != NULL)
        ber_free(ber, 0);
    ldap_msgfree(result);
    ldap_unbind(ld);

    return 0;
}
