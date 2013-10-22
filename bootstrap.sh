# $Id$
# $URL: $

# bootstrap - script to bootstrap the distribution rolling engine

# usage:
#  $ sh ./bootstrap && ./configure && make dist[check]
#
# this yields a tarball which one can install doing
#
#  $ tar zxf PACKAGENAME-*.tar.gz
#  $ cd PACKAGENAME-*
#  $ ./configure
#  $ make
#  # make install

# requirements:
#  GNU autoconf, from e.g. ftp.gnu.org:/pub/gnu/autoconf/
#  GNU automake, from e.g. http://ftp.gnu.org/gnu/automake/

automake=automake
aclocal=aclocal

# if you want to autogenerate a ChangeLog form svn:
#
#  svn2cl, a python script, as used in the GNU Enterprise project.
#    By jcater (Jason Cater), contributions by reinhard (Reinhard Müller).
#    Get it from
#    http://www.gnuenterprise.org/cgi-bin/viewcvs.cgi/*checkout*/gnue/trunk/gnue-common/utils/svn2cl .
#    svn2cl is used in Makefile.am too.
#
# (Another svn2cl implementation, in perl, is at
# http://www.contactor.se/~dast/svn/archive-2002-04/0910.shtml)
#
# see also toplevel Makefile.am

# test -f ChangeLog || {
#   svn log --verbose > ChangeLog
#}

if $automake --version|head -1 |grep ' 1\.[4-9]'; then
    echo "automake 1.4-1.9 is active. You should use automake 1.10 or later"
    if test -f /etc/debian_version; then
        echo " sudo apt-get install automake"
        echo " sudo update-alternatives --config automake"
    fi
    exit 1
fi
# autoconf-archive Debian package, aclocal-archive RPM, obsolete/badly supported OS, installed in home dir
acdirs="/usr/share/autoconf-archive/ /usr/share/aclocal/ /usr/local/share/aclocal/ $HOME/local/share/autoconf-archive/"

found=false
for d in $acdirs
do
    if test -f ${d}libtool.m4
    then
        found=true
        break
    fi
done

if ! $found
then
    cat <<EOT
You need the autoconf-archive package, or the aclocal-archive package.
EOT
fi

# Debian automake package installs as automake-version.  Use this
# to make sure the right automake is being used.
# if not installed, use: apt-get install automake1.9

AUTOMAKE=automake ACLOCAL=aclocal autoreconf --install \
      --symlink

# add --make if you want to run "make" too.

# autoreconf should run something like:
#
# aclocal-1.9 \
#     && automake-1.9 --add-missing --verbose --gnu \
#     && autoconf

