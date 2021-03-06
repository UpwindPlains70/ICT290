// C++/WinRT v1.0.190111.3

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once
#include "winrt/impl/Windows.Devices.Enumeration.1.h"
#include "winrt/impl/Windows.UI.1.h"
#include "winrt/impl/Windows.UI.Core.1.h"
#include "winrt/impl/Windows.UI.Popups.1.h"
#include "winrt/impl/Windows.UI.WindowManagement.1.h"
#include "winrt/impl/Windows.UI.ViewManagement.1.h"

WINRT_EXPORT namespace winrt::Windows::UI::ViewManagement {

}

namespace winrt::impl {

}

WINRT_EXPORT namespace winrt::Windows::UI::ViewManagement {

struct WINRT_EBO AccessibilitySettings :
    Windows::UI::ViewManagement::IAccessibilitySettings
{
    AccessibilitySettings(std::nullptr_t) noexcept {}
    AccessibilitySettings();
};

struct WINRT_EBO ActivationViewSwitcher :
    Windows::UI::ViewManagement::IActivationViewSwitcher
{
    ActivationViewSwitcher(std::nullptr_t) noexcept {}
};

struct WINRT_EBO ApplicationView :
    Windows::UI::ViewManagement::IApplicationView,
    impl::require<ApplicationView, Windows::UI::ViewManagement::IApplicationView2, Windows::UI::ViewManagement::IApplicationView3, Windows::UI::ViewManagement::IApplicationView4, Windows::UI::ViewManagement::IApplicationView7, Windows::UI::ViewManagement::IApplicationView9, Windows::UI::ViewManagement::IApplicationViewWithContext>
{
    ApplicationView(std::nullptr_t) noexcept {}
    static bool TryUnsnapToFullscreen();
    static int32_t GetApplicationViewIdForWindow(Windows::UI::Core::ICoreWindow const& window);
    static Windows::UI::ViewManagement::ApplicationViewState Value();
    static bool TryUnsnap();
    static Windows::UI::ViewManagement::ApplicationView GetForCurrentView();
    static bool TerminateAppOnFinalViewClose();
    static void TerminateAppOnFinalViewClose(bool value);
    static Windows::UI::ViewManagement::ApplicationViewWindowingMode PreferredLaunchWindowingMode();
    static void PreferredLaunchWindowingMode(Windows::UI::ViewManagement::ApplicationViewWindowingMode const& value);
    static Windows::Foundation::Size PreferredLaunchViewSize();
    static void PreferredLaunchViewSize(Windows::Foundation::Size const& value);
    static void ClearAllPersistedState();
    static void ClearPersistedState(param::hstring const& key);
};

struct WINRT_EBO ApplicationViewConsolidatedEventArgs :
    Windows::UI::ViewManagement::IApplicationViewConsolidatedEventArgs,
    impl::require<ApplicationViewConsolidatedEventArgs, Windows::UI::ViewManagement::IApplicationViewConsolidatedEventArgs2>
{
    ApplicationViewConsolidatedEventArgs(std::nullptr_t) noexcept {}
};

struct WINRT_EBO ApplicationViewScaling :
    Windows::UI::ViewManagement::IApplicationViewScaling
{
    ApplicationViewScaling(std::nullptr_t) noexcept {}
    static bool DisableLayoutScaling();
    static bool TrySetDisableLayoutScaling(bool disableLayoutScaling);
};

struct ApplicationViewSwitcher
{
    ApplicationViewSwitcher() = delete;
    static void DisableShowingMainViewOnActivation();
    static Windows::Foundation::IAsyncOperation<bool> TryShowAsStandaloneAsync(int32_t viewId);
    static Windows::Foundation::IAsyncOperation<bool> TryShowAsStandaloneAsync(int32_t viewId, Windows::UI::ViewManagement::ViewSizePreference const& sizePreference);
    static Windows::Foundation::IAsyncOperation<bool> TryShowAsStandaloneAsync(int32_t viewId, Windows::UI::ViewManagement::ViewSizePreference const& sizePreference, int32_t anchorViewId, Windows::UI::ViewManagement::ViewSizePreference const& anchorSizePreference);
    static Windows::Foundation::IAsyncAction SwitchAsync(int32_t viewId);
    static Windows::Foundation::IAsyncAction SwitchAsync(int32_t toViewId, int32_t fromViewId);
    static Windows::Foundation::IAsyncAction SwitchAsync(int32_t toViewId, int32_t fromViewId, Windows::UI::ViewManagement::ApplicationViewSwitchingOptions const& options);
    static Windows::Foundation::IAsyncOperation<bool> PrepareForCustomAnimatedSwitchAsync(int32_t toViewId, int32_t fromViewId, Windows::UI::ViewManagement::ApplicationViewSwitchingOptions const& options);
    static void DisableSystemViewActivationPolicy();
    static Windows::Foundation::IAsyncOperation<bool> TryShowAsViewModeAsync(int32_t viewId, Windows::UI::ViewManagement::ApplicationViewMode const& viewMode);
    static Windows::Foundation::IAsyncOperation<bool> TryShowAsViewModeAsync(int32_t viewId, Windows::UI::ViewManagement::ApplicationViewMode const& viewMode, Windows::UI::ViewManagement::ViewModePreferences const& viewModePreferences);
};

struct WINRT_EBO ApplicationViewTitleBar :
    Windows::UI::ViewManagement::IApplicationViewTitleBar
{
    ApplicationViewTitleBar(std::nullptr_t) noexcept {}
};

struct WINRT_EBO ApplicationViewTransferContext :
    Windows::UI::ViewManagement::IApplicationViewTransferContext
{
    ApplicationViewTransferContext(std::nullptr_t) noexcept {}
    ApplicationViewTransferContext();
    static hstring DataPackageFormatId();
};

struct WINRT_EBO InputPane :
    Windows::UI::ViewManagement::IInputPane,
    impl::require<InputPane, Windows::UI::ViewManagement::IInputPane2, Windows::UI::ViewManagement::IInputPaneControl>
{
    InputPane(std::nullptr_t) noexcept {}
    static Windows::UI::ViewManagement::InputPane GetForCurrentView();
    static Windows::UI::ViewManagement::InputPane GetForUIContext(Windows::UI::UIContext const& context);
};

struct WINRT_EBO InputPaneVisibilityEventArgs :
    Windows::UI::ViewManagement::IInputPaneVisibilityEventArgs
{
    InputPaneVisibilityEventArgs(std::nullptr_t) noexcept {}
};

struct ProjectionManager
{
    ProjectionManager() = delete;
    static Windows::Foundation::IAsyncAction StartProjectingAsync(int32_t projectionViewId, int32_t anchorViewId);
    static Windows::Foundation::IAsyncAction SwapDisplaysForViewsAsync(int32_t projectionViewId, int32_t anchorViewId);
    static Windows::Foundation::IAsyncAction StopProjectingAsync(int32_t projectionViewId, int32_t anchorViewId);
    static bool ProjectionDisplayAvailable();
    static winrt::event_token ProjectionDisplayAvailableChanged(Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler);
    using ProjectionDisplayAvailableChanged_revoker = impl::factory_event_revoker<Windows::UI::ViewManagement::IProjectionManagerStatics, &impl::abi_t<Windows::UI::ViewManagement::IProjectionManagerStatics>::remove_ProjectionDisplayAvailableChanged>;
    static ProjectionDisplayAvailableChanged_revoker ProjectionDisplayAvailableChanged(auto_revoke_t, Windows::Foundation::EventHandler<Windows::Foundation::IInspectable> const& handler);
    static void ProjectionDisplayAvailableChanged(winrt::event_token const& token);
    static Windows::Foundation::IAsyncAction StartProjectingAsync(int32_t projectionViewId, int32_t anchorViewId, Windows::Devices::Enumeration::DeviceInformation const& displayDeviceInfo);
    static Windows::Foundation::IAsyncOperation<bool> RequestStartProjectingAsync(int32_t projectionViewId, int32_t anchorViewId, Windows::Foundation::Rect const& selection);
    static Windows::Foundation::IAsyncOperation<bool> RequestStartProjectingAsync(int32_t projectionViewId, int32_t anchorViewId, Windows::Foundation::Rect const& selection, Windows::UI::Popups::Placement const& prefferedPlacement);
    static hstring GetDeviceSelector();
};

struct WINRT_EBO StatusBar :
    Windows::UI::ViewManagement::IStatusBar
{
    StatusBar(std::nullptr_t) noexcept {}
    static Windows::UI::ViewManagement::StatusBar GetForCurrentView();
};

struct WINRT_EBO StatusBarProgressIndicator :
    Windows::UI::ViewManagement::IStatusBarProgressIndicator
{
    StatusBarProgressIndicator(std::nullptr_t) noexcept {}
};

struct WINRT_EBO UISettings :
    Windows::UI::ViewManagement::IUISettings,
    impl::require<UISettings, Windows::UI::ViewManagement::IUISettings2, Windows::UI::ViewManagement::IUISettings3, Windows::UI::ViewManagement::IUISettings4, Windows::UI::ViewManagement::IUISettings5>
{
    UISettings(std::nullptr_t) noexcept {}
    UISettings();
};

struct WINRT_EBO UISettingsAutoHideScrollBarsChangedEventArgs :
    Windows::UI::ViewManagement::IUISettingsAutoHideScrollBarsChangedEventArgs
{
    UISettingsAutoHideScrollBarsChangedEventArgs(std::nullptr_t) noexcept {}
};

struct WINRT_EBO UIViewSettings :
    Windows::UI::ViewManagement::IUIViewSettings
{
    UIViewSettings(std::nullptr_t) noexcept {}
    static Windows::UI::ViewManagement::UIViewSettings GetForCurrentView();
};

struct WINRT_EBO ViewModePreferences :
    Windows::UI::ViewManagement::IViewModePreferences
{
    ViewModePreferences(std::nullptr_t) noexcept {}
    static Windows::UI::ViewManagement::ViewModePreferences CreateDefault(Windows::UI::ViewManagement::ApplicationViewMode const& mode);
};

}
