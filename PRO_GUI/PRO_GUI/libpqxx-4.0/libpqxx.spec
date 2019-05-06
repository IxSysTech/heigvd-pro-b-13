Summary: C++ API to the PostgreSQL database management system.
Name: libpqxx
Version: 4.0
Release: 1
License: BSD
Group: Development/Libraries
Source: ftp://pqxx.org/software/libpqxx/libpqxx-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-root
URL: http://pqxx.org/
Vendor:    Andromeda Technology & Automation
Packager:  Arjen Baart <arjen@andromeda.nl>
Requires: postgresql-libs
BuildRequires: postgresql-devel
Prefix: %{_prefix}
Docdir: %{_docdir}

%description
This is the official C++ client API for postgres.  What libpqxx brings you is
effective use of templates to reduce the inconvenience of dealing with type
conversions; of standard C++ strings to keep you from having to worry about
buffer allocation and overflow attacks; of exceptions to take the tedious and
error-prone plumbing around error handling out of your hands; of constructors
and destructors to bring resource management under control; and even basic
object-orientation to give you some extra reliability features that would be
hard to get with most other database interfaces.

%package devel
Summary: Libraries, includes, etc. to develop PostgreSQL applications in C++.
Group: Development/Libraries
Requires: libpqxx = %{version}

%description devel
Libraries, include files, etc you can use to develop PostgreSQL applications in C++.

%prep
%setup -q

%build
%configure --enable-shared
make 

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-, root, root)
%doc AUTHORS ChangeLog NEWS README COPYING
%{_libdir}/lib*.so

%files devel
%defattr(-, root, root)
%{_libdir}/*a
%{_libdir}/pkgconfig/libpqxx.pc
%{_includedir}/*
%{_bindir}/pqxx-config

%changelog

* Thu Jan 29 2004 Arjen Baart <arjen@andromeda.nl>

- Built release 2.1.3

