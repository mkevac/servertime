mod_servertime.la: mod_servertime.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  mod_servertime.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_servertime.la
