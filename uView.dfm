object fView: TfView
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'fView'
  ClientHeight = 193
  ClientWidth = 428
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = mmMenu
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object sgView: TStringGrid
    Left = 0
    Top = 3
    Width = 425
    Height = 187
    DefaultColWidth = 80
    FixedCols = 0
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Yu Gothic UI'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object mmMenu: TMainMenu
    Left = 376
    Top = 65520
    object miSort: TMenuItem
      Caption = #1057#1086#1088#1090#1080#1088#1086#1074#1082#1072
      object miByCategory: TMenuItem
        AutoCheck = True
        Caption = #1055#1086' '#1082#1072#1090#1077#1075#1086#1088#1080#1103#1084
        RadioItem = True
        OnClick = miSortClick
      end
      object miBySum: TMenuItem
        Tag = 1
        AutoCheck = True
        Caption = #1055#1086' '#1089#1091#1084#1084#1077
        RadioItem = True
        OnClick = miSortClick
      end
      object miOld: TMenuItem
        Tag = 2
        AutoCheck = True
        Caption = #1057#1085#1072#1095#1072#1083#1072' '#1089#1090#1072#1088#1099#1077
        RadioItem = True
        OnClick = miSortClick
      end
      object miNew: TMenuItem
        Tag = 3
        AutoCheck = True
        Caption = #1057#1085#1072#1095#1072#1083#1072' '#1085#1086#1074#1099#1077
        RadioItem = True
        OnClick = miSortClick
      end
    end
    object miSum: TMenuItem
      Caption = #1043#1088#1091#1087#1087#1080#1088#1086#1074#1082#1072' '#1087#1086' '#1076#1072#1090#1077
      OnClick = miSumClick
      object miForWeek: TMenuItem
        AutoCheck = True
        Caption = #1047#1072' '#1085#1077#1076#1077#1083#1102
        RadioItem = True
        OnClick = miSumClick
      end
      object miForMonth: TMenuItem
        AutoCheck = True
        Caption = #1047#1072' '#1084#1077#1089#1103#1094
        RadioItem = True
        OnClick = miSumClick
      end
      object miForYear: TMenuItem
        AutoCheck = True
        Caption = #1047#1072' '#1075#1086#1076
        RadioItem = True
        OnClick = miSumClick
      end
    end
    object miSumOfGroup: TMenuItem
      Caption = #1057#1091#1084#1084#1072' '#1087#1086' '#1074#1099#1073#1086#1088#1082#1077
      OnClick = miSumOfGroupClick
    end
  end
end
