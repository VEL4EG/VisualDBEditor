@echo off
SetLocal EnableDelayedExpansion
(set PATH=D:\Qt\5.9.1\mingw53_32\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=D:\Qt\5.9.1\mingw53_32\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=D:\Qt\5.9.1\mingw53_32\plugins
)
%*
EndLocal
