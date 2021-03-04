% First, get and read the signal
[voice, fs] = audioread('Recording.m4a');
voice = voice';
time = 0 : 1/fs : (length(voice)-1)/fs;
subplot(3, 2, 1);
plot(time, voice);
title('Original Voice')

% Frequency Spectrum
voice_freq = fftshift(fft(voice));
freq = -fs/2 : fs/(length(voice_freq)-1) : fs/2;
subplot(3, 2, 2);
plot(freq, abs(voice_freq));
title('Frequency Spectrum of the Signal');

%Generate Blue Noise
blue = dsp.ColoredNoise('Color', "blue", 'SamplesPerFrame', length(voice));
blueNoise = blue();
blueNoise = blueNoise' / max(blueNoise)/10;
subplot(3, 2, 3);
plot(time, blueNoise);
title('Blue Noise');

% Frequency Spectrum of blueNoise
blueNoise_freq = fftshift(fft(blueNoise));
subplot(3, 2, 4);
plot(freq, abs(blueNoise_freq));
title('Frequency Spectrum of the Blue Noise')

%Adding Blue Noise to the Voice
bVoice = voice+blueNoise;
subplot(3, 2, 5);
plot(time, bVoice);
title('Adding Blue Noise to Voice');

% Frequency Spectrum of voice+noise
bVoice_freq = fftshift(fft(bVoice));
subplot(3, 2, 6);
plot(freq, abs(bVoice_freq));
title('Frequency Spectrum of the Voice+Noise')