#include "myFFmpegImageStream.h"

myFFmpegImageStream::myFFmpegImageStream()
{
    avcodec_register_all();
}

int myFFmpegImageStream::getFrame(int *got_frame, std::string & filename)
{
    AVFormatContext * p_format_context = 0;
    *got_frame = 0;

    ///打开文件
    int ret = avformat_open_input(&p_format_context, filename.c_str(), NULL, NULL);
    if (ret < 0)
    {
        std::cout << "avformat_open_input failed" << std::endl;
    }

    ///从文件中提取流信息
    ret = avformat_find_stream_info(p_format_context, NULL);
    if (ret < 0)
    {
        std::cout << "avformat_find_stream_info failed" << std::endl;
    }

    for (int i = 0; i < p_format_context->nb_streams; i++) {
        AVStream *stream;
        AVFrame * frame;
        AVPacket *pkt;
        AVCodecContext *codec_ctx;
        stream = p_format_context->streams[i];
        codec_ctx = stream->codec;
        std::cout << "streams count : " << p_format_context->nb_streams << std::endl;
        std::cout << "codec_id : " << codec_ctx->codec_id << std::endl;
        std::cout << "codec_type : " << codec_ctx->codec_type << std::endl;

        AV_CODEC_ID_4GV;
        /* Reencode video & audio and remux subtitles etc. */
        ///在多个数据流中找到视频流 video stream（类型为MEDIA_TYPE_VIDEO）
        if (codec_ctx->codec_type == AVMEDIA_TYPE_VIDEO) {
            /* Open decoder */
            ///查找video stream 相对应的解码器 avcodec_find_decoder
            ///打开解码器 avcodec_open2()
            ret = avcodec_open2(codec_ctx,
                    avcodec_find_decoder(codec_ctx->codec_id), NULL);
            if (ret < 0) {
//                av_log(NULL, AV_LOG_ERROR, "Failed to open decoder for stream #%u\n", i);
                std::cout << "avcodec_open2 failed" << std::endl;
                return ret;
            }

            ///为解码帧分配内存
            frame = av_frame_alloc();

            ///从流中读取读取数据到Packet中
            av_read_frame(p_format_context, pkt);


            ///对video 帧进行解码
            avcodec_decode_video2(codec_ctx, frame, got_frame, pkt);

//            decode_packet();
        }
    }

    std::cout <<"over"<<std::endl;

    return 0;
}
