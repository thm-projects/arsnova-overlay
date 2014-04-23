# required metadata
sonar.projectKey=de.thm.arsnova:arsnova-overlay-10
sonar.projectName=ARSnova Overlay
sonar.projectVersion=@VERSION_SHORT@
  
# path to source directories (required)
sonar.sources=src

# The value of the property must be the key of the language.
sonar.language=c++

sonar.cxx.suffixes.sources=cpp
sonar.cxx.xunit.reportPath=*Test.xml
sonar.cxx.coverage.reportPath=coverage.xml
sonar.cxx.valgrind.reportPath=*Test.memcheck
sonar.cxx.cppcheck.reportPath=cppcheck.xml
sonar.cxx.cppncss.reportPath=cppncss.xml
  
sonar.scm.url=scm:git:git://scm.thm.de/arsnova/arsnovaoverlay.git

# exclude qt created files
sonar.exclusions=**/ui_*.h