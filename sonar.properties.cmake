# required metadata
sonar.projectKey=de.thm.arsnova:ARSnovaDesktop
sonar.projectName=ARSnovaDesktop
sonar.projectVersion=@VERSION_SHORT@
  
# path to source directories (required)
sonar.sources=src

# The value of the property must be the key of the language.
sonar.language=c++

sonar.cxx.suffixes.sources=cpp
sonar.cxx.xunit.reportPath=*Test.xml
sonar.cxx.coverage.reportPath=coverage.xml
sonar.cxx.valgrind.reportPath=*Test.memcheck
  
sonar.scm.url=scm:git:git://scm.thm.de/arsnova/arsnovadesktop.git

# exclude qt created files
sonar.exclusions=**/ui_*.h