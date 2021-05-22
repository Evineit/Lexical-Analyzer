if (state >= 100 && state <= 128)
{
    if (state == 100 && !(std::find(std::begin(reservedWords), std::end(reservedWords), token) != std::end(reservedWords)))
    {
        state = 101;
    }
    else if (state == 125)
    {
        token.append(sourceText[i]);
        appendToken(state, token);
        token = "";
        state = 0;
        continue;
    }
    appendToken(state, token);
    // Set current char as the start of a new token if this was the cause of a final state
    if (relacionar(sourceText[i]) < 27)
    {
        token = sourceText[i];
        state = states[0][relacionar(sourceText[i])];
    }
    else
    {
        token = "";
        state = 0;
    }
}
else if (state >= 500)
{
    errorToken(state);
    return;
}