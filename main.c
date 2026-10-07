#include <stdio.h>

// Khai bao cau truc tai khoan nguoi dung
struct UserAccount {
    int user_id;
    char username[50];
    int plan_type;      // 1: Free, 2: Personal, 3: Family
    int days_overdue;
    int active_devices;
    long final_fee;     // Phi thuc thu cuoi cung (VND)
};

int main() {
    struct UserAccount accounts[100];
    int n, i;
    long total_revenue = 0;
    int downgraded_count = 0;

    // Nhap so luong tai khoan
    printf("=== HE THONG QUAN LY SUBSCRIPTION STREAMFLOW ===\n");
    do {
        printf("Nhap so luong tai khoan can rà soat (1-100): ");
        scanf("%d", &n);
        if (n < 1 || n > 100) {
            printf("[Loi] So luong khong hop le. Vui long nhap lai.\n");
        }
    } while (n < 1 || n > 100);

    // BƯỚC 1: NHẬP VÀ KIỂM SOÁT LỖI DỮ LIỆU
    for (i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin tai khoan thu %d ---\n", i + 1);
        printf("Ma tai khoan (user_id): ");
        scanf("%d", &accounts[i].user_id);
        
        printf("Ten tai khoan (username): ");
        scanf(" %[^\n]", accounts[i].username);

        // Kiem soat du lieu rac bang do-while
        do {
            printf("Loai goi hien tai (1-Free, 2-Personal, 3-Family): ");
            scanf("%d", &accounts[i].plan_type);
            if (accounts[i].plan_type < 1 || accounts[i].plan_type > 3) {
                printf("  [Loi] Ma goi khong ton tai. Hay nhap lai (1, 2, hoac 3)!\n");
            }
        } while (accounts[i].plan_type < 1 || accounts[i].plan_type > 3);

        do {
            printf("So ngay no cuoc (days_overdue >= 0): ");
            scanf("%d", &accounts[i].days_overdue);
            if (accounts[i].days_overdue < 0) {
                printf("  [Loi] So ngay no cuoc khong the am. Hay nhap lai!\n");
            }
        } while (accounts[i].days_overdue < 0);

        do {
            printf("So thiet bi dang ket noi (active_devices >= 0): ");
            scanf("%d", &accounts[i].active_devices);
            if (accounts[i].active_devices < 0) {
                printf("  [Loi] So thiet bi khong the am. Hay nhap lai!\n");
            }
        } while (accounts[i].active_devices < 0);
    }

    // BƯỚC 2: XỬ LÝ NGHIỆP VỤ (ĐỐI SOÁT & HẠ CẤP)
    for (i = 0; i < n; i++) {
        // Gán phí cơ bản ban đầu theo gói
        if (accounts[i].plan_type == 1) {
            accounts[i].final_fee = 0;
        } else if (accounts[i].plan_type == 2) {
            accounts[i].final_fee = 120000;
        } else if (accounts[i].plan_type == 3) {
            accounts[i].final_fee = 250000;
        }

        // Quy tắc 1: Hạ cấp do nợ cước >= 3 ngày
        if (accounts[i].days_overdue >= 3) {
            if (accounts[i].plan_type != 1) {
                downgraded_count++; // Ghi nhan da ha cap
            }
            accounts[i].plan_type = 1; // Chuyen ve Free
            accounts[i].final_fee = 0; // Xoa no cuoc thang nay (Khong thu phi)
        }

        // Quy tắc 2: Phụ thu vi phạm thiết bị gói Personal (Chỉ áp dụng nếu hiện đang là gói 2)
        // Lưu ý: Nếu bị hạ cấp ở Quy tắc 1 thì plan_type đã là 1, sẽ tự động bỏ qua khối lệnh này
        if (accounts[i].plan_type == 2 && accounts[i].active_devices > 1) {
            int extra_devices = accounts[i].active_devices - 1;
            accounts[i].final_fee += extra_devices * 30000;
        }

        // Tích luỹ doanh thu
        total_revenue += accounts[i].final_fee;
    }

    // BƯỚC 3: IN BÁO CÁO TỔNG KẾT
    printf("\n============================================ BANG TONG HOP KET QUA RA SOAT ============================================\n");
    printf("%-10s %-25s %-15s %-15s %-15s %-20s\n", 
           "MA TK", "TEN TAI KHOAN", "MA GOI (Moi)", "SO THIET BI", "NGAY NO CUOC", "PHI THUC THU (VND)");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        printf("%-10d %-25s %-15d %-15d %-15d %-20ld\n", 
               accounts[i].user_id, 
               accounts[i].username, 
               accounts[i].plan_type, 
               accounts[i].active_devices, 
               accounts[i].days_overdue, 
               accounts[i].final_fee);
    }
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
    printf("[*] TONG DOANH THU THUC TE TRONG KY : %ld VND\n", total_revenue);
    printf("[*] TONG SO TAI KHOAN BI HA CAP     : %d tai khoan\n", downgraded_count);
    printf("=======================================================================================================================\n");

    return 0;
}