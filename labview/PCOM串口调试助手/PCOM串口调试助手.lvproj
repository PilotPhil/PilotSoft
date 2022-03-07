<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="19008000">
	<Item Name="我的电脑" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">我的电脑/VI服务器</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">我的电脑/VI服务器</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="FVI" Type="Folder" URL="../FVI">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="PCOM.ico" Type="Document" URL="../PCOM.ico"/>
		<Item Name="PCOM串口调试助手.vi" Type="VI" URL="../PCOM串口调试助手.vi"/>
		<Item Name="依赖关系" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
			<Item Name="串口初始化.vi" Type="VI" URL="/C/Users/63291/Desktop/上位机设计2020.2.4/子VI/3.串口/串口初始化.vi"/>
			<Item Name="串口读取.vi" Type="VI" URL="/C/Users/63291/Desktop/上位机设计2020.2.4/子VI/3.串口/串口读取.vi"/>
			<Item Name="串口发送.vi" Type="VI" URL="/C/Users/63291/Desktop/上位机设计2020.2.4/子VI/3.串口/串口发送.vi"/>
			<Item Name="串口关闭.vi" Type="VI" URL="/C/Users/63291/Desktop/上位机设计2020.2.4/子VI/3.串口/串口关闭.vi"/>
			<Item Name="延时1ms.vi" Type="VI" URL="/C/Users/63291/Desktop/上位机设计2020.2.4/子VI/6.其他/延时1ms.vi"/>
		</Item>
		<Item Name="程序生成规范" Type="Build">
			<Item Name="PCOM串口调试助手" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{43F8AB66-6645-4C12-8CBC-A04DD05A8984}</Property>
				<Property Name="App_INI_GUID" Type="Str">{61514A9C-E61D-453B-8CD0-1070F94F3D0A}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{64591632-DBA6-4147-B0E6-B8BBFC0D9B07}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">PCOM串口调试助手</Property>
				<Property Name="Bld_defaultLanguage" Type="Str">ChineseS</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/PCOM串口调试助手</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{BC55CB80-542E-49B9-B93A-857CADF0ABD0}</Property>
				<Property Name="Bld_version.build" Type="Int">2</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">PCOM.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/PCOM串口调试助手/PCOM.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">支持目录</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/PCOM串口调试助手/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Exe_actXinfo_enumCLSID[0]" Type="Str">{31DEF79F-A840-417A-9646-FEE8B415C816}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[1]" Type="Str">{EB912781-DB1B-4123-B963-73ACF2AEFDF2}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[10]" Type="Str">{B49414A7-CCCA-4300-AB24-BB65630B61CB}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[11]" Type="Str">{3CBE7D7D-EBBE-4175-A9E0-560D3DC79C4C}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[12]" Type="Str">{DCA8A17D-7EDD-49AB-9A9A-353F70536446}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[13]" Type="Str">{C5F5B026-58C3-475E-AB2B-2325078BDC45}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[14]" Type="Str">{5F890877-7158-4813-B8ED-04725D87CC23}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[15]" Type="Str">{9CB4D208-BBDA-4D3F-BEE9-1EEC0E7FD6CF}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[16]" Type="Str">{F2568822-514A-404B-B4CC-29FFB14BFB25}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[2]" Type="Str">{BFF75F81-0D6B-4EB2-B362-F56BBA5B4304}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[3]" Type="Str">{1DA2FD77-21A4-4581-B44D-BF12BB3A6EFF}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[4]" Type="Str">{9325751C-8B7C-4414-9EC6-E3C19DFAFDA9}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[5]" Type="Str">{B443B5DB-30D4-495A-A998-4104290B7B6E}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[6]" Type="Str">{C6736C22-75BE-4BFF-B600-A4864EB79351}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[7]" Type="Str">{4BA12D8D-92F4-4AB5-A1C1-CC851F02FEEF}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[8]" Type="Str">{B214F1E4-04B1-4B3C-B400-3FA0327685F2}</Property>
				<Property Name="Exe_actXinfo_enumCLSID[9]" Type="Str">{11DC7DAC-EBA5-4071-A1C9-96AA2906F2E8}</Property>
				<Property Name="Exe_actXinfo_enumCLSIDsCount" Type="Int">17</Property>
				<Property Name="Exe_actXinfo_majorVersion" Type="Int">5</Property>
				<Property Name="Exe_actXinfo_minorVersion" Type="Int">5</Property>
				<Property Name="Exe_actXinfo_objCLSID[0]" Type="Str">{D7FF9B09-770A-48C3-80F7-A073970B37A9}</Property>
				<Property Name="Exe_actXinfo_objCLSID[1]" Type="Str">{D54B34E0-864C-47AA-8107-C0B90AC4CFB8}</Property>
				<Property Name="Exe_actXinfo_objCLSID[10]" Type="Str">{62A9202F-C294-4A83-A9A4-28054F16D4EF}</Property>
				<Property Name="Exe_actXinfo_objCLSID[11]" Type="Str">{2B734F02-20CC-4CC2-80FE-61B4A2090672}</Property>
				<Property Name="Exe_actXinfo_objCLSID[12]" Type="Str">{9ED648CA-2DEE-40C6-B01F-2A1FDB65ED2F}</Property>
				<Property Name="Exe_actXinfo_objCLSID[13]" Type="Str">{8B55F828-A02E-48F5-9975-C996EA679DF5}</Property>
				<Property Name="Exe_actXinfo_objCLSID[2]" Type="Str">{E15F42D6-3E8A-4B7A-A0FA-2BA0945D81A1}</Property>
				<Property Name="Exe_actXinfo_objCLSID[3]" Type="Str">{04488923-1873-480D-894B-457C1A228FC4}</Property>
				<Property Name="Exe_actXinfo_objCLSID[4]" Type="Str">{CA4FD1D8-DE00-4C1E-9249-90835DA962A5}</Property>
				<Property Name="Exe_actXinfo_objCLSID[5]" Type="Str">{DBD63FE2-318F-41DA-95AD-4C05A931F1FD}</Property>
				<Property Name="Exe_actXinfo_objCLSID[6]" Type="Str">{A820C21D-6D31-444D-928E-BFB23C96C936}</Property>
				<Property Name="Exe_actXinfo_objCLSID[7]" Type="Str">{D1B21EBE-97B7-41E8-A233-1A712B14B7BD}</Property>
				<Property Name="Exe_actXinfo_objCLSID[8]" Type="Str">{65D111D8-B58E-4B4A-936A-F36262A1E7B2}</Property>
				<Property Name="Exe_actXinfo_objCLSID[9]" Type="Str">{2C7F442A-1E89-499C-9B42-4580D35FF26E}</Property>
				<Property Name="Exe_actXinfo_objCLSIDsCount" Type="Int">14</Property>
				<Property Name="Exe_actXinfo_progIDPrefix" Type="Str">PCOM</Property>
				<Property Name="Exe_actXServerName" Type="Str">PCOM</Property>
				<Property Name="Exe_actXServerNameGUID" Type="Str">{6EDC0A24-CA28-4860-BBE1-CF5B7A4418AD}</Property>
				<Property Name="Exe_iconItemID" Type="Ref">/我的电脑/PCOM.ico</Property>
				<Property Name="Source[0].itemID" Type="Str">{FB4E5EDB-4A56-4ED3-ADD8-DA20B9814FA3}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/我的电脑/PCOM串口调试助手.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[2].itemID" Type="Ref">/我的电脑/FVI/Delay1ms.vi</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">VI</Property>
				<Property Name="Source[3].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[3].itemID" Type="Ref">/我的电脑/FVI/NowTime.vi</Property>
				<Property Name="Source[3].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[3].type" Type="Str">VI</Property>
				<Property Name="Source[4].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[4].itemID" Type="Ref">/我的电脑/FVI/Serial.vi</Property>
				<Property Name="Source[4].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[4].type" Type="Str">VI</Property>
				<Property Name="Source[5].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[5].itemID" Type="Ref">/我的电脑/FVI/SerialClose.vi</Property>
				<Property Name="Source[5].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[5].type" Type="Str">VI</Property>
				<Property Name="Source[6].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[6].itemID" Type="Ref">/我的电脑/FVI/SerialRead.vi</Property>
				<Property Name="Source[6].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[6].type" Type="Str">VI</Property>
				<Property Name="Source[7].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[7].itemID" Type="Ref">/我的电脑/FVI/SerialSend.vi</Property>
				<Property Name="Source[7].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[7].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">8</Property>
				<Property Name="TgtF_fileDescription" Type="Str">PCOM串口调试助手</Property>
				<Property Name="TgtF_internalName" Type="Str">PCOM串口调试助手</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">版权 2020 </Property>
				<Property Name="TgtF_productName" Type="Str">PCOM串口调试助手</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{CAE426E8-A955-48AD-BE8F-972315F332E1}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">PCOM.exe</Property>
				<Property Name="TgtF_versionIndependent" Type="Bool">true</Property>
			</Item>
		</Item>
	</Item>
</Project>
