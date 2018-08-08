
ldap.c描述用C语言和ldap交互的过程，C语言在客户端执行，
访问服务器端的ldap服务，TCP连接由ldap库提供的接口函数
维护，调用的各种接口函数说明如下：
ldap_initialize：初始化一个ld描述符，唯一标识一个连接，
	供后续调用使用
ldap_set_option：设置连接属性，协议是必须设置的
ldap_simple_bind_s：建立到ldap服务器的连接
ldap_search_ext_s：根据指定查询条件查询表项
ldap_first_entry：取满足查询条件的若干表项中的第一个
ldap_next_entry：取满足查询条件的若干表项中的下一个
ldap_get_dn：获取一个表项的DN
ldap_first_attribute：取一个表项的第一个条目
ldap_next_attribute：取一个表项的下一个条目
ldap_get_value_len：取一个条目中的所有属性名和属性值
ldap_unbind：关闭一个连接

具体函数入参可以查看man，带后缀_s的函数表示是同步调用，
会阻塞

start.sh描述编译C语言需要的ldap链接库
