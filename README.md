BÁO CÁO BÀI TẬP LỚP MÔN LẬP TRÌNH NÂNG CAO
Sinh viên: Nguyễn Đức Mạnh – 24020219               	Sinh ngày: 26/11/2006
Ngành học: Công nghệ thông tin                               	Lớp: 2425II_INT2215_3
Tên game: Flappy Bird 
1.Thông tin game:
- Link Github: https://github.com/nguyenmanh6911/sdl2game
- Game tham khảo: Flappy Bird
- Link demo Youtube: https://www.youtube.com/watch?v=Ql05RmbM9B4&t=10s
2. Lối chơi, logic của game: 
-Game được lấy ý tưởng từ game Flappy Bird gốc nhưng đã được cải tiến với nhiều chế độ chơi và vật phẩm mới.
* Chế độ chơi :
1 Player Mode: Người chơi điều khiển chú chim bay qua các ống bằng cách nhấn phím Space hoặc chuột trái. Khi chọn chế độ này, người chơi sẽ phải nhập tên và sau đó có thể chọn 1 trong 3 level 1,2, hoặc 3.
Trong đó:
+ Level 1: Tương tự với game Flappy Bird gốc, người chơi đơn thuần điều khiển chú chim vượt qua các ống, mỗi khi qua một ống sẽ được cộng 1 điểm.
+ Level 2: Ở level này, game sẽ xuất hiện thêm vật phẩm bomb, bổ huyết, đồng thời tốc độ di chuyển nhanh hơn level 1.
+ Level 3: Tương tự như ở level 2 nhưng tốc độ sẽ nhanh hơn.
2 Player Mode: Trước khi chơi sẽ phải nhập tên của player 1 và player 2. Hai người chơi điều khiển 2 chú chim trên màn hình cùng 1 lúc. Người chơi 1 dùng phím Space để điều khiển, người chơi 2 dùng chuột trái để điều khiển. Người nào va phải chướng ngại vật trước sẽ thua.
Vật phẩm đặc biệt:
+ Bomb: Xuất hiện ngẫu nhiên xuyên suốt trò chơi ở level 2 và 3, nếu chạm vào sẽ thua ngay lập tức.
+ Bổ huyết: Xuất hiện tối đa 2 lần trong 1 ván chơi. Nếu chạm vào người chơi sẽ được tăng thêm 1 mạng. Khi va chạm với vật thể, người chơi sẽ được hồi sinh lại vị trí ban đầu và tiếp tục tính điểm. Trong trường hợp đó, vật phẩm này sẽ không xuất hiện lại trong xuyên suốt thời gian còn lại.
Xếp hạng: Game có hệ thống bảng xếp hạng, lưu lại top 5 người chơi có điểm số cao nhất cùng với tên của họ. Mỗi level sẽ có 1 bảng xếp hạng riêng biệt và chỉ áp dụng cho chế độ chơi 1 người.
* Logic chính của game:
Game sử dụng SDL2 để xử lí đồ hoạ, âm thanh, sự kiện. Các thuật toán chính bao gồm:
+ Xử lí toạ độ của các đối tượng trong game
+ Xử lí va chạm giữa chim với ống và vật phẩm
+ Lưu trữ và hiển thị điểm số trong bảng xếp hạng
Đồ họa, âm thanh: 
* Hình ảnh: Game sử dụng tất cả 24 hình ảnh khác nhau bao gồm cả hình ảnh nền và hình ảnh các đối tượng trong game.
* Âm thanh: Game có tổng cộng 3 âm thanh hiệu ứng và 1 âm thanh nền
* Hoạt ảnh:
+ Chuyển động liên tục của ống và nền tạo cảm giác liền mạch, mượt mà
+ Chim vỗ cánh liên tục tạo cảm giác như đang chuyển động

3. Cấu trúc của project game:
* Cấu trúc của game được chia ra thành 3 phần chính:
- Phần mở đầu game: Menu cho có các tuỳ chọn như chọn chế độ chơi, hướng dẫn, bật tắt âm thanh và thoát game 
- Phần chọn chế độ: Khi người chơi chọn chế độ 1 người chơi, người chơi sẽ phải nhập playername rồi sau đó game sẽ hiển thị ra màn hình có 3 level để người chơi để chọn level muốn chơi. Còn khi người chơi chọn chế độ chơi 2 người, 2 người chơi sẽ lần lượt nhập vào playername1, playername2 và sau đó có thể chơi.
- Phần game chính: Người chơi điều khiển chim, tránh ống và bomb và thu thập vật phẩm để có thể đạt được điểm số cao nhất có thể
- Phần kết thúc game:
+Ở chế độ chơi 1 người: Hiển thị điểm số, cho phép người chơi chơi lại, xem xếp hạng top 5 người có điểm cao nhất, quay trở lại màn hình ban đầu (Menu)  hoặc thoát game.
+Ở chế độ chơi 2 người: Thông báo tên người chơi giành chiến thắng, cho phép người chơi chơi lại, quay trở lại màn hình ban đầu (Menu) hoặc thoát game.

4. Các chức năng đã cài được cho game:
- Phần mở đầu game:
+ Tắt hoặc bật âm thanh trong quá trình chơi
+ Chọn chế độ 1 hoặc 2 người chơi (Sau khi chọn chế độ chơi, người chơi sẽ phải nhập playername,nếu chọn chế độ 1 người chơi thì sẽ tiếp tục chọn level)
+ Cửa sổ hướng dẫn cách chơi

- Phần game chính:
+ Màn hình hiển thị chú chim, các ống, bomb và vật phẩm chuyển động 
+ Hiển thị số mạng ở góc trái màn hình, số điểm đang chơi và số điểm cao nhất
+ Mỗi khi chim va chạm với bomb, ống hoặc rơi ra khỏi màn hình thì số mạng sẽ trừ đi 1 cho đến khi số mạng bằng 0 thì sẽ game sẽ kết thúc
+ Có âm thanh hiệu ứng khi chim vỗ cánh, đập tường và khi tăng điểm.

- Phần kết thúc game:
+ Hiển thị số điểm trong ván vừa chơi
+ Chức năng chơi lại
+ Chức năng quay lại màn hình bắt đầu 
+ Chức năng xem bảng xếp hạng của top 5 người chơi có điểm cao nhất 
+ Chức năng thoát game

5. Các công cụ hỗ trợ bài làm:
- Về phần code: ChatGpt, Lazyfoo, Youtube, Google
- Chỉnh sửa ảnh: Canva, remove.bg
- Chỉnh sửa âm thanh: Convertio, mp3cut.net
- Tìm font chữ: Google Fonts, 1001freefonts

6. Nguồn tư liệu
-Âm thanh: Youtube,Pixabay, Free Sound
-Hình ảnh: Pinterest, Google
-Font chữ: Google Fonts, 1001freefonts
-Ý tưởng game: game Flappy Bird truyền thống




