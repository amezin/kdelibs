cp -f /d/qt/5/qtbase-cli_parser/src/corelib/tools/qcommand* .
perl -pi -e 's/Q_CORE_EXPORT/KDEQT5STAGING_EXPORT/g' qc*.h
perl -pi -e 's/QtCore\///' qc*.h
perl -pi -e '$_ = "#include \"kdeqt5staging_export.h\"\n" . $_ if (/qstringlist.h/)' qcommandlineoption.h
#echo Do not forget to make the constructor and destructor for QCommandLineParser public again.
patch -R qcommandlineparser.h <<EOF
@@ -83,10 +81,8 @@ protected:
 private:
     Q_DISABLE_COPY(QCommandLineParser)
 
-public: // HACK FOR KDEQT5STAGING
     QCommandLineParser();
     ~QCommandLineParser();
-private:
 
     QCommandLineParserPrivate* const d;
 };
EOF