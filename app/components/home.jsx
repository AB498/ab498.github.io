(() => {
    let Component = (props) => {
        let { children } = props || {};
        return <div>
            <div>Home{uuid().slice(0, 5)}</div>
            {children}
        </div>
    }

    return Component;
})()