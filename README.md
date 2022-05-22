1.	Hướng dẫn cách lấy file code.
-	Bước 1: Chọn Fork ở góc trên bên phải để liên kết nơi lưu trữ này đến tài khoản của bạn.
-	Bước 2: Đến thư mục bạn muốn lưu trữ, nhấn chuột phải chọn terminal hoặc gitBash xong gõ câu lệnh:
-	git clone https://github.com/[YOUR_USERNAME]/SHOOTING_GAME.git
-	Bước 3: Thoát cửa sổ lệnh. Giờ đây file đã được copy vào nơi lưu trữ của bạn.

2.	Mô tả Game:
-	Trò chơi tương tự như game Contra cổ điển nhưng đơn giản hơn.
-	Bạn điều khiển một nhân vật có thể di chuyển tự do, hãy cẩn thận với những quái vật cản đường bạn và những khe vực sâu.
-	Chú ý bạn chỉ có 3 mạng hãy cẩn thận!
-	Giới hạn thời gian là 300s, bạn hãy cố gắng đánh bại quái vật 1 cách nhanh nhất có thể, nếu không bạn sẽ thua!
-	Hãy dùng khẩu súng của bạn một cách hợp lý để tiêu diệt quái vật và tích điểm nhiều nhất có thể.
-	Trên đường đi có những đồng tiền, hãy ăn nó, nó có thể giúp ích bạn nhiều đấy!
-	Đích đến là 1 lá cờ, bạn chỉ cần đến đó => bạn sẽ chiến thắng.
-	Chú ý: có 2 loại quái vật (đều được 1 điểm khi tiêu diệt):
-	Những con quái vật không thể di chuyển được nhưng bắn laser từ miệng mình.
-	Những con quái vật di chuyển quanh một khu vực nhất định.
-	Boss cuối nằm ở gần vạch đích.
-	Hãy cẩn thận vì nếu bạn va phải quái vật hay trúng đạn, bạn sẽ mất 1 mạng.
-	Hãy đánh bại và chinh phục trò chơi!

3.	Chức năng của Game:
-	Link youtube mình review qua game này: https://youtu.be/xqD1p3c9Cv0
-	Dấu "X" bên phải màn hình nếu bạn muốn thoát trò chơi.
-	Thanh trên cùng hiển thị chỉ số mạng, số coin, điểm và giới hạn thời gian.
-	Các con quái vật xuất hiện ngẫu nhiên trên bản đồ, tiêu diệt => cộng điểm.
-	Các khối block hình kim cương, có thể ăn.
-	Dùng dấu mũi tên LEFT, RIGHT trên bàn phím để di chuyển nhân vật.
-	Nút Chuột Trái dùng để bắn và nút Chuột Phải dùng để nhảy.
-	Có thể bắn sang trái, phải.
-	Chạm vào cây cờ cuối bản đồ để giành chiến thắng.

4.	Kỹ thuật được sử dụng trong dự án:
-	thư viện SDL2.0, SDL_image và SDL_ttf.
-	sử dụng thêm các file hình ảnh, font chữ bên ngoài.
-	mảng, mảng con trỏ, mảng vector.
-	sử dụng truy xuất tệp dữ diệu bên ngoài (file.dat ...).
-	sử dụng lớp class: tính đóng gói, tính kế thừa,... để tạo các đối tượng.
-	sử dụng tách file .h, .cpp để dễ quản lý và phân ra từng chức năng.
-	sử dụng các vòng lặp, biến toàn cục, biến static,...
-	thuật toán xử lý va chạm giữa các đối tượng.

5.	Kết luận & Hướng phát triển:

(1)	 Kết luận: Về cơ bản mình thấy game khá ổn định. Tuy nhiên, bên cạnh đó trò chơi mình vẫn còn một vài chỗ thiếu xót:
-	Hình ảnh vẫn còn chưa đẹp.
-	Vẫn còn một vài lỗi nhỏ.
-	Bản đồ vẫn còn quá nhỏ.
-	Ăn tiền chưa biết làm gì.
-	Chưa có hiệu ứng âm thanh
-	Chưa thể lưu điểm của người chơi sau mỗi lần chơi.
-	Chưa thể lưu tiến độ của người chơi.

(2)	 Hướng phát triển:
Mình dự kiến thêm tính năng khác:
-	Tạo thêm menu (gồm có phần play, tutorial, setting) => Giúp trải nghiệm chơi được nâng cao hơn
-	Thêm boss cuối => Tăng tính thử thách cho game.
-	Lưu tiến độ của người chơi => Có thể chơi tiếp phần đang chơi dở lần trước, không phải chơi lại từ đầu nếu bạn thoát game.
-	Mở rộng bản đồ => Thêm các loại map và quái vật khác nhau.
-	Có cửa hàng, đồng tiền bạn ăn được bạn có thể mua súng, trang bị áo giáp khác xịn hơn.
-	Bảng xếp hạng lưu điểm và tên của người chơi có thành tích cao.
-	Thêm nhạc cho game để trải nghiệm game được tốt hơn.

(3)	Tâm đắc:
Khi làm dự án, mình đã rất khó khăn giai đoạn đầu vì lần đầu tiếp xúc đến thư viện SDL và phải xây dựng một tựa game cho riêng mình.
Nhưng bên cạnh đó đem lại cho mình nhiều lợi ích:
-	Học quy trình tạo ra sản phẩm.
-	Giúp mình có khả năng tự học, tự tìm tòi những kiến thức mới và những nguồn trên mạng.
-	Xây dựng mình một tính cách cẩn thận, chu đáo, làm việc có kế hoạch, biết chia nhỏ từng phần công việc để xử lý:
-	Tách file => Xây dựng từng đối tượng đơn lẻ => Gộp chung lại thành 1 đối tượng lớn hơn.
-	Việc làm bài tập lớn này giúp cho khả năng cũng như hiểu biết của mình về ngôn ngữ C++ được cải thiện đáng kể khi phải làm quen với nhiều dữ liệu mới.
-	Dần dần học được cách clean code, refactor.

ĐÂY LÀ NHỮNG CHIA SẺ MÌNH SAU MỘT THỜI GIAN DÀI HOÀN THÀNH BÀI TẬP LỚN NÀY. MONG SẼ GIÚP ÍCH BẠN ĐƯỢC PHẦN NÀO.

CẢM ƠN BẠN VÌ ĐÃ QUAN TÂM!
