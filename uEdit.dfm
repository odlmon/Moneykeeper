object fEdit: TfEdit
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Form1'
  ClientHeight = 295
  ClientWidth = 690
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object lSum: TLabel
    Left = 430
    Top = 83
    Width = 52
    Height = 21
    Caption = #1056#1072#1089#1093#1086#1076':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
  end
  object lDate: TLabel
    Left = 430
    Top = 119
    Width = 37
    Height = 21
    Caption = #1044#1072#1090#1072':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
  end
  object lRepeat: TLabel
    Left = 430
    Top = 160
    Width = 90
    Height = 21
    Caption = #1055#1086#1074#1090#1086#1088#1077#1085#1080#1077':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
  end
  object lName: TLabel
    Left = 430
    Top = 15
    Width = 71
    Height = 21
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
  end
  object lCategory: TLabel
    Left = 430
    Top = 47
    Width = 76
    Height = 21
    Caption = #1050#1072#1090#1077#1075#1086#1088#1080#1103':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
  end
  object sgEdit: TStringGrid
    Left = 1
    Top = 0
    Width = 425
    Height = 244
    DefaultColWidth = 80
    FixedCols = 0
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
    OnSelectCell = sgEditSelectCell
  end
  object cpCalendarPicker: TCalendarPicker
    Left = 526
    Top = 115
    Width = 156
    Height = 32
    CalendarHeaderInfo.DaysOfWeekFont.Charset = DEFAULT_CHARSET
    CalendarHeaderInfo.DaysOfWeekFont.Color = clWindowText
    CalendarHeaderInfo.DaysOfWeekFont.Height = -13
    CalendarHeaderInfo.DaysOfWeekFont.Name = 'Segoe UI'
    CalendarHeaderInfo.DaysOfWeekFont.Style = []
    CalendarHeaderInfo.Font.Charset = DEFAULT_CHARSET
    CalendarHeaderInfo.Font.Color = clWindowText
    CalendarHeaderInfo.Font.Height = -20
    CalendarHeaderInfo.Font.Name = 'Segoe UI'
    CalendarHeaderInfo.Font.Style = []
    Color = clWindow
    Date = 43802.000000000000000000
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    IsEmpty = False
    ParentFont = False
    TabOrder = 1
    TextHint = 'select a date'
  end
  object eSum: TEdit
    Left = 526
    Top = 80
    Width = 156
    Height = 29
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
  end
  object cbRepeat: TComboBox
    Left = 526
    Top = 157
    Width = 156
    Height = 29
    Style = csDropDownList
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 3
    Text = #1053#1077#1090
    Items.Strings = (
      #1053#1077#1090
      #1045#1078#1077#1076#1085#1077#1074#1085#1086
      #1050#1072#1078#1076#1099#1077' 2 '#1076#1085#1103
      #1041#1091#1076#1085#1080#1077' '#1076#1085#1080
      #1042#1099#1093#1086#1076#1085#1099#1077' '#1076#1085#1080
      #1045#1078#1077#1085#1077#1076#1077#1083#1100#1085#1086
      #1050#1072#1078#1076#1099#1077' 2 '#1085#1077#1076#1077#1083#1080
      #1050#1072#1078#1076#1099#1077' 4 '#1085#1077#1076#1077#1083#1080
      #1045#1078#1077#1084#1077#1089#1103#1095#1085#1086
      #1050#1072#1078#1076#1099#1077' 2 '#1084#1077#1089#1103#1094#1072
      #1050#1072#1078#1076#1099#1077' 3 '#1084#1077#1089#1103#1094#1072
      #1050#1072#1078#1076#1099#1077' 6 '#1084#1077#1089#1103#1094#1077#1074
      #1045#1078#1077#1075#1086#1076#1085#1086)
  end
  object eName: TEdit
    Left = 526
    Top = 13
    Width = 156
    Height = 29
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object cbCategory: TComboBox
    Left = 526
    Top = 48
    Width = 156
    Height = 29
    Style = csDropDownList
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    Items.Strings = (
      #1055#1088#1086#1076#1091#1082#1090#1099
      #1050#1072#1092#1077
      #1044#1086#1089#1091#1075
      #1058#1088#1072#1085#1089#1087#1086#1088#1090
      #1047#1076#1086#1088#1086#1074#1100#1077
      #1055#1086#1076#1072#1088#1082#1080
      #1057#1077#1084#1100#1103
      #1055#1086#1082#1091#1087#1082#1080)
  end
  object bEdit: TButton
    Left = 430
    Top = 208
    Width = 118
    Height = 36
    Caption = #1048#1079#1084#1077#1085#1080#1090#1100
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    OnClick = bEditClick
  end
  object bDelete: TButton
    Left = 564
    Top = 208
    Width = 118
    Height = 36
    Caption = #1059#1076#1072#1083#1080#1090#1100
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    OnClick = bDeleteClick
  end
  object bAdd: TButton
    Left = 432
    Top = 250
    Width = 250
    Height = 36
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 8
    OnClick = bAddClick
  end
end
