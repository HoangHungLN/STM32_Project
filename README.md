# Project: Traffic Light System

**Môn học:** Vi xử lý - Vi điều khiển (CO3009)  
**Học kỳ:** HK 1, năm học 2025 - 2026  
**Giảng viên hướng dẫn:** TS. Lê Trọng Nhân  

**Thành viên nhóm:** 
- Nguyễn Văn Hùng - 2311301  
- Lại Nguyễn Hoàng Hưng - 2311327  

---

## 1. Tổng quan dự án (Overview)
Project xây dựng hệ thống mô phỏng đèn giao thông tại một ngã tư sử dụng vi điều khiển STM32.  

Hệ thống bao gồm các thành phần chính:
- **6 đèn LED:** 2 đèn đỏ, 2 đèn vàng (amber), 2 đèn xanh (green) để mô phỏng 2 trục đường.
- **1 màn hình LCD I2C:** Hiển thị thời gian (số giây) và thông tin của từng trạng thái đèn.
- **3 nút nhấn (Button):** Điều khiển chuyển đổi chế độ và thay đổi thông số hệ thống.

---

## 2. Các chế độ hoạt động (Operating Modes)
Hệ thống được thiết kế theo mô hình Máy trạng thái (FSM) với 3 chế độ chính:

1. **Chế độ NORMAL (Tự động):** Hệ thống đèn giao thông hoạt động tự động như bình thường. Màn hình LCD hiển thị số giây đếm ngược.
2. **Chế độ MODIFY (Điều chỉnh):** - Cho phép người dùng cấu hình lại thời gian sáng của từng loại đèn: Đỏ (Modify_Red), Vàng (Modify_Amber), Xanh (Modify_Green).
   - Có tính năng bảo vệ và đồng bộ tự động: Đảm bảo tổng thời gian đèn Xanh + Vàng luôn bằng thời gian đèn Đỏ. Nếu cấu hình sai lệch, hệ thống sẽ tự động hiệu chỉnh lại cho hợp lý.
3. **Chế độ MANUAL (Thủ công):** Người dùng có thể tự chuyển đổi các trạng thái đèn (RED_GREEN, RED_AMBER, GREEN_RED, AMBER_RED) thủ công thông qua nút bấm.

---

## 3. Cấu hình phần cứng (Hardware & Pinout)
Dự án được triển khai trên mạch phát triển **STM32F103RBTx (LQFP64)**.

| Thành phần | Vi điều khiển | Ghi chú |
| :--- | :--- | :--- |
| **Đèn trục X** | PA8 (xLED1), PA9 (xLED2) | 01: Vàng, 10: Xanh, 11: Đỏ |
| **Đèn trục Y** | PC7 (yLED1), PB6 (yLED2) | 01: Vàng, 10: Xanh, 11: Đỏ |
| **Nút nhấn 1** | PB3 | Điều chỉnh thời gian / Trạng thái Manual |
| **Nút nhấn 2** | PB5 | Xác nhận / Chuyển sang Manual |
| **Nút nhấn 3** | PB4 | (Phím bổ trợ chuyển mode) |
| **LCD I2C** | PB9 (SDA), PB8 (SCL) | Giao tiếp I2C1 |

---

## 4. Cấu trúc phần mềm (Software Architecture)
Hệ thống sử dụng cơ chế Scheduler (bộ định thời) để điều phối các tác vụ (tasks) hoạt động một cách mượt mà và đa nhiệm. 

Cấu trúc các module (dựa trên cấu trúc file `.c`/`.h`):
- **Core Scheduler & Timer:**
  - `scheduler.c`: Quản lý việc thêm (Add) và phân phối (Dispatch) các tác vụ cần chạy ở mỗi chu kỳ.
  - `software_timer.c`: Xử lý hệ thống định thời bằng phần mềm cho các sự kiện của đèn giao thông.
- **Peripheral Drivers:**
  - `button.c`: Đọc trạng thái nút nhấn với giải thuật chống rung (debounce).
  - `i2c-lcd.c`: Thư viện giao tiếp màn hình Text LCD 16x2 thông qua I2C.
  - `traffic_display.c`: Module đóng gói các hàm hiển thị giao diện đèn và thời gian (`Traffic_Display_Update`, `Traffic_Display_Manual`).
- **FSM Application logic:**
  - `normalTraffic.c`: Máy trạng thái quản lý chu kỳ tự động.
  - `modifyTime.c`: Máy trạng thái quản lý việc cài đặt đếm ngược.
  - `manualTraffic.c`: Máy trạng thái quản lý điều khiển thủ công.
