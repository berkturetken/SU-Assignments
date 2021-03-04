function[outputSignal,time]=addingSignals(signal1,time1,signal2,time2)
    if( length(signal1) >= length(signal2))
        outputSignal=signal1;
        time=time1;
    else
        outputSignal=signal2;
        time=time2;
    end
   
i=1;
while(i<=min(length(time1),length(time2)))
    outputSignal(i)=signal1(i)+signal2(i);
    i=i+1;
end

function [signal,time]  = SignalGenerator(signalType,Amplitude,frequency,timeLimit)
    time = 0:0.01:timeLimit;
    if strcmp(signalType,"sin")
        signal=Amplitude*sin(2*pi*frequency*time);
    elseif strcmp(signalType,"cos")
        signal=Amplitude*sin(2*pi*frequency*time);
    else
        disp('Signal type is not appropriate')
       
    end
function[outputSignal,entryTime]=SimpleChannel(entrySignal,entryTime)
    noise=rand(1,501);
    outputSignal=addingSignals(entrySignal,entryTime,noise,entryTime);
    plot(entryTime,outputSignal);
end


[s1,t1]=SignalGenerator('cos',2,1,5);
[s2,t2]=SignalGenerator('cos',3,2,5);
[s3,t3]=addingSignals(s1,t1,s2,t2);


plot(t3,s3);
title('without noise');
hold on;
[s4,t4]=SimpleChannel(s3,t3);

plot(t4,s4)
title('with noise');
xlabel('time');
ylabel('amplitude');