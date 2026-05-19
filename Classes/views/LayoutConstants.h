#pragma once

/**
 * @brief 全局布局常量
 *
 * 集中定义设计分辨率、主牌区/堆牌区高度等。
 * 调整视觉效果时仅需修改本文件。
 */
namespace LayoutConstants
{
    /** 设计分辨率宽度 */
    constexpr float kDesignWidth = 1080.0f;

    /** 设计分辨率高度 */
    constexpr float kDesignHeight = 2080.0f;

    /** 主牌区高度（位于屏幕上半部分） */
    constexpr float kPlayfieldHeight = 1500.0f;

    /** 堆牌区高度（位于屏幕下半部分） */
    constexpr float kStackHeight = 580.0f;
}
