@echo off
g:\works\cpp\FlexYacc\test\bison   -d -oTestParserY.cpp TestParser.y
g:\works\cpp\FlexYacc\test\flex   -oTestParserL.cpp TestParser.lex

if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: ĳ�����ߴ�����λ�÷����˴������: "����ִ��Ԥ�����¼�..."
exit 1
:VCEnd